#pragma once
#ifndef filter_hpp__
#define filter_hpp__

#include "../../../types.hpp"

#include <boost/range/algorithm/for_each.hpp>

#include <vector>

namespace mysql {

enum directions {

    undefined = 0x0,
    asc,
    desc

};

class filter
{
public:
    struct limit
    {
        limit() :
            from(-1), quantity(-1)
        {
        };

        limit( const int& quantity_ ) :
            from(-1), quantity(quantity_)
        {
        };

        limit( const int& from_, const int& quantity_ ) :
            from(from_), quantity(quantity_)
        {
        };

        int from;
        int quantity;
    };

private:
    template< typename order_t >
    class order_group :
        public std::vector< order_t >
    {
    public:
        order_group()
        {
        };

        order_group( const order_t& o )
        {
            push_back( o );
        };

        inline order_group& operator&( const order_t& o )
        {
            push_back( o );
            return *this;
        };

        inline filter operator|( const limit& limit_ )
        {
            filter f(*this);
            return std::move( f | limit_ );
        };
    };

public:
    struct order_by
    {
        order_by()
        {
        };

        order_by( const tstring& name_, const directions& direction_ = asc ) :
            name(name_)
        {
            direction = (direction_ == desc) ? _T("DESC") : _T("ASC");
        };
   
        inline order_group< order_by > operator&( const order_by& o )
        {
            order_group< order_by > order_group_(*this);
            return std::move( order_group_ & o );
        };

        inline filter operator|( const limit& limit_ )
        {
            filter f(*this);
            return std::move( f | limit_ );
        };

        tstring name;
        tstring direction;
    };

// ORDER block definition
public:
    typedef order_group< order_by > order_group_type;

private:
    template< typename where_t >
    class where_group :
        public std::vector< where_t >
    {
    public:
        where_group()
        {
        };

        where_group( const where_t& w )
        {
            push_back( w );
        };

        const tstring& op( const size_t& at ) const
        {
            return ops[at];
        };

        inline where_group& operator&&( const where_t& w )
        {
            return operator_( w, _T("AND") );
        };

        inline where_group& operator||( const where_t& w )
        {
            return operator_( w, _T("OR") );
        };

        inline where_group& operator&&( const where_group& wg )
        {
            boost::range::for_each( wg, [&]( where_t w ) {
                operator_( w, _T("AND") );
            });

            return *this;
        };

        inline where_group& operator||( const where_group& wg )
        {
            boost::range::for_each( wg, [&]( where_t w ) {
                operator_( w, _T("OR") );
            });

            return *this;
        };

        inline filter& operator|( const limit& limit_ )
        {
            return std::move( filter(*this, limit_) );
        };

        inline filter& operator|( const order_by& order_ )
        {
            return std::move( filter(*this, order_group_type(order_)) );
        };

        inline filter& operator|( const order_group_type& order_group_ )
        {
            return std::move( filter(*this, order_group_) );
        };

    private:
        inline where_group& operator_( const where_t& w, const tstring& op )
        {
            push_back( w );
            ops.push_back( op );
            return *this;
        };

    private:
        std::vector< tstring > ops;
    };

public:
    struct where
    {
        where()
        {
        };

        where( const tstring& name_ ) :
            name(name_)
        {
        };

        template< typename T >
        inline where& operator=( const T& value_ )
        {
        #if UNICODE
            std::wostringstream stream;
        #else
            std::ostringstream  stream;
        #endif
            stream << value_;
            value = stream.str();
            return *this;
        };

        inline where_group< where > operator&&( const where& w )
        {
            where_group< where > where_group_( *this );
            return std::move( where_group_ && w );
        };

        inline where_group< where > operator||( const where& w )
        {
            where_group< where > where_group_( *this );
            return std::move( where_group_ || w );
        };

        inline filter& operator&&( filter& f )
        {
            return f && *this;
        };

        inline filter& operator||( filter& f )
        {
            return f || *this;
        };

        inline filter operator|( const limit& limit_ )
        {
            return std::move( filter(*this, limit_) );
        };

        inline filter operator|( const order_by& order_ )
        {
            return std::move( filter(*this, order_group_type(order_)) );
        };

        inline filter operator|( const order_group_type& order_group_ )
        {
            return std::move( filter(*this, order_group_) );
        };

        tstring name;
        tstring value;
    };

// WHERE block definition
public:
    typedef where_group< where > where_group_type;

public:
    filter();
    filter( const limit& limit__ );
    filter( const order_by& order__ );
    filter( const order_group_type& order_group__ );
    filter( const where& where__, const limit& limit__ = limit() );
    filter( const where_group_type& where_group__, const limit& limit__ = limit() );
    filter( const where_group_type& where_group__, const order_group_type& order_group__ );

public:
    inline filter& operator&&( const where_group_type& wg )
    {
        where_group_ && wg;
        return *this;
    };

    inline filter& operator||( const where_group_type& wg )
    {
        where_group_ || wg;
        return *this;
    };

    inline filter& operator|( const limit& limit__ )
    {
        limit_ = limit__;
        return *this;
    };

public:
    tstring toString();

private:
    tstring wheres_toString();
    tstring orders_toString();
    tstring limit_toString();

private:
    where_group_type where_group_;
    order_group_type order_group_;
    limit            limit_;
};

typedef filter::where    where;
typedef filter::order_by order_by;
typedef filter::limit    limit;

} // namespace mysql

#endif // filter_hpp__
