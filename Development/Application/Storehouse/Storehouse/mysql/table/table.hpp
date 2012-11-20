#pragma once
#ifndef table_hpp__
#define table_hpp__

#include "../../types.hpp"
#include "../query/filter/filter.hpp"

#include <boost/any.hpp>
#include <boost/lexical_cast.hpp>

#include <vector>

namespace mysql {

class table
{
// Row prototype definition
private:
    template< typename field_t >
    class row_prototype :
        public std::vector< field_t >
    {
    public:
        row_prototype()
        {
        };

        row_prototype( const field_t& f )
        {
            push_back( f );
        };

        template< typename T >
        inline row_prototype& operator=( const T& f )
        {
            push_back( f );
            return *this;
        };

        template< typename T >
        inline row_prototype& operator|( const T& f )
        {
        #if UNICODE
            std::wostringstream stream;
        #else
            std::ostringstream  stream;
        #endif
            stream << f;
            push_back( stream.str() );
            return *this;
        };
    };

// Field prototype definition
private:
    template< typename value_t >
    class field_prototype
    {
    public:
        template< typename T >
        field_prototype( const T& v ) :
            val(v)
        {
        };

        field_prototype( const field_prototype& other ) :
            val(other.val)
        {
        };

        inline const value_t& value() const
        {
            return val;
        };

        template< typename T >
        inline const T any_value() const
        {
            try
            {
                return boost::any_cast< T >( val );
            }
            catch (boost::bad_any_cast&)
            {
                return T();
            }
        };

        template< typename T, typename T2 >
        inline const T any_value() const
        {
            try
            {
                return boost::lexical_cast< T >( boost::any_cast< T2 >( val ) );
            }
            catch (boost::bad_lexical_cast&)
            {
                return T();
            }
        };

        template< typename T >
        inline row_prototype< field_prototype > operator|( const T& v )
        {
            row_prototype< field_prototype > row_prototype_( *this );
            return std::move( row_prototype_ | v );
        };

    private:
        value_t val;
    };

// Header field definition
public:
    typedef field_prototype< tstring > header_field;

// Header definition
public:
    typedef row_prototype< header_field > header_type;

// Result field definition
public:
    typedef field_prototype< boost::any > result_field;

// Row definition
public:
    typedef row_prototype< result_field > row_type;

// Content definition
public:
    typedef std::vector< row_type > content_type;

public:
    table();
    table( const tstring& name__ );
    table( const tstring& name__, const header_type& header__ );

public:
    bool load( const filter& filter__ = filter() );

    bool save_insert( const filter& filter__ = filter() );

    bool save_update( const filter& filter__ = filter() );

    bool delete_( const filter& filter__ = filter() );

    const tstring& getName() const;

    header_type& getHeader();

    void setContent( content_type&& content__ );

    content_type::iterator begin();
    content_type::iterator end();
    content_type::size_type size() const;
    bool empty() const;
    void clear();

private:
    tstring      name_;
    header_type  header_;
    content_type content_;
};

} // namespace mysql

#endif // table_hpp__
