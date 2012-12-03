#include "stdafx.h"

#include "mysql.hpp"

#include <boost/date_time.hpp>

namespace mysql {

mysql_impl::mysql_impl()
{
}

mysql_impl::~mysql_impl()
{
    close();
}

BOOL mysql_impl::createODBC( HWND hWnd, WORD fRequest, LPCSTR lpszDriver, LPCSTR lpszAttributes )
{
    HINSTANCE dllHandle = NULL;
    FARPROC   farProc   = NULL;

    dllHandle = LoadLibrary( _T("odbccp32.dll") );

    if (NULL != dllHandle)
    {
        farProc = GetProcAddress( dllHandle, "SQLConfigDataSource" );

        if (farProc != NULL)
        {
            ODBC MyFunction;
            MyFunction = ODBC( farProc );

            MyFunction( hWnd, fRequest, lpszDriver, lpszAttributes );
        }

        FreeLibrary( dllHandle );
    }

    return farProc != NULL;
}

BOOL mysql_impl::connect( tstring& host,
                          const tstring& odbc,
                          const tstring& database,
                          const tstring& user,
                          const tstring& pass )
{
    close();

    try
    {
        if (host.empty()) host = _T("127.0.0.1"); // localhost
        if (odbc.empty() || database.empty() || user.empty()) return FALSE;

        USES_CONVERSION;
        CStringA creatingString;
        creatingString.Format( "DSN=%s;SERVER=%s;DATABASE=%s;UID=%s;PWD=%s;",
            W2A( odbc.c_str() ),
            W2A( host.c_str() ),
            W2A( database.c_str() ),
            W2A( user.c_str() ),
            W2A( pass.c_str() ) );
        if (!createODBC( NULL, ODBC_ADD_SYS_DSN, "MySQL ODBC 5.1 Driver", creatingString ))
            return FALSE;

        CString connectionString;
        connectionString.Format( _T("DSN=%s;SERVER=%s;UID=%s;PWD=%s;"),
            odbc.c_str(), host.c_str(), user.c_str(), pass.c_str() );

        recordSet.m_pDatabase = &mysql_;

        mysql_.SetLoginTimeout( 2 );
        mysql_.SetQueryTimeout( 5 );

        return mysql_.OpenEx( connectionString, CDatabase::noOdbcDialog);
    }
    catch (CException* e) { UNREFERENCED_PARAMETER( e ); }

    return FALSE;
}

void mysql_impl::close()
{
    try
    {
        if (recordSet.IsOpen())
            recordSet.Close();

        if (isConnected())
            mysql_.Close();
    }
    catch (CException* e) { UNREFERENCED_PARAMETER( e ); }
}

BOOL mysql_impl::isConnected()
{
    try
    {
        return mysql_.IsOpen();
    }
    catch (CException* e) { UNREFERENCED_PARAMETER( e ); }

    return FALSE;
}


table::content_type mysql_impl::execute_query_select( const tstring& query_string )
{
    if (!isConnected())
        return std::move( table::content_type() );

    recordSet.Open( CRecordset::snapshot, query_string.c_str(), CRecordset::readOnly );

    table::content_type content_;

    short      fields(recordSet.GetODBCFieldCount());
    CDBVariant cbdVarValue;

    while (!recordSet.IsEOF())
    {
        table::row_type row_;

        for (short i = 0; i < fields; ++i)
        {
            recordSet.GetFieldValue( i, cbdVarValue );

            switch (cbdVarValue.m_dwType)
            {
            case DBVT_BOOL:
                row_.push_back( cbdVarValue.m_boolVal );
                break;

            case DBVT_UCHAR: // tinyint
                row_.push_back( cbdVarValue.m_chVal );
                break;

            case DBVT_SHORT: // smallint, year
                row_.push_back( cbdVarValue.m_iVal );
                break;

            case DBVT_LONG: // int, mediumint
                row_.push_back( cbdVarValue.m_lVal );
                break;

            case DBVT_SINGLE: // float
                row_.push_back( cbdVarValue.m_fltVal );
                break;

            case DBVT_DOUBLE: // double
                row_.push_back( cbdVarValue.m_dblVal );
                break;

            case DBVT_DATE: // date, datetime, time (incorrect), timestamp
                {
                    using namespace boost::gregorian;
                    using namespace boost::posix_time;
                    row_.push_back(
                        ptime(
                            date(
                                cbdVarValue.m_pdate->year,
                                cbdVarValue.m_pdate->month,
                                cbdVarValue.m_pdate->day
                            ),
                            hours(cbdVarValue.m_pdate->hour) +
                            minutes(cbdVarValue.m_pdate->minute) + 
                            seconds(cbdVarValue.m_pdate->second)
                        )
                    );
                }
                break;

            case DBVT_STRING:
                row_.push_back( tstring(*cbdVarValue.m_pstring) );
                break;

            case DBVT_ASTRING:
                row_.push_back( std::string(*cbdVarValue.m_pstringA) );
                break;

            case DBVT_WSTRING: // bigint, decimal, char, varchar, tinytext, text, mediumtext, longtext 
                row_.push_back( std::wstring(*cbdVarValue.m_pstringW) );
                break;

            default:
                row_.push_back( 0 );
                break;
            }
        }

        content_.push_back( row_ );

        recordSet.MoveNext();
    }

    recordSet.Close();

    return std::move( content_ );
}

void mysql_impl::execute_query( const tstring& query_string )
{
    if (!isConnected())
        return;

    mysql_.ExecuteSQL( query_string.c_str() );
}

} // namespace mysql
