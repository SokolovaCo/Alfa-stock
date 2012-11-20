#pragma once
#ifndef mysql_hpp__
#define mysql_hpp__

#include "afxdb.h"
#include <odbcinst.h>

#include "../types.hpp"
#include "table/table.hpp"
#include "../singleton.hpp"
#include "mysql_settings.hpp"

#include <boost/thread/mutex.hpp>

namespace mysql {

class mysql_impl
{
public:
    mysql_impl();
    ~mysql_impl();

public:

    BOOL connect( tstring& host,
                  const tstring& odbc,
                  const tstring& database,
                  const tstring& user,
                  const tstring& pass );

    void close();

    BOOL isConnected();

    table::content_type execute_query_select( const tstring& query_string );
    void execute_query( const tstring& query_string );

private:
    BOOL createODBC( HWND hWnd,
                     WORD fRequest,
                     LPCSTR lpszDriver,
                     LPCSTR lpszAttributes );

private:
    CDatabase    mysql_;
    CRecordset   recordSet;
    boost::mutex asyncGuard;
};

typedef bool (__stdcall *ODBC)(HWND hwndParent, WORD fRequest, LPCSTR lpszDriver, LPCSTR lpszAttributes);

typedef singleton< mysql::mysql_impl > mysql;

namespace private_
{
    static mysql::ForceInit forceInitMySQL;
}

} // namespace mysql

#endif // mysql_hpp__
