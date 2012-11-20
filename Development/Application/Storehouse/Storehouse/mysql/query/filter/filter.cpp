#include "stdafx.h"

#include "filter.hpp"

#include <boost/range/algorithm/for_each.hpp>
#include <boost/lexical_cast.hpp>

namespace mysql {

filter::filter()
{
}

filter::filter( const limit& limit__ ) :
    limit_(limit__)
{
}

filter::filter( const order_by& order__ ) :
    order_group_(order__)
{
}

filter::filter( const order_group_type& order_group__ ) :
    order_group_(order_group__)
{
}

filter::filter( const where& where__, const limit& limit__ ) :
    where_group_(where__),
    limit_(limit__)
{
}

filter::filter( const where_group_type& where_group__, const limit& limit__ ) :
    where_group_(where_group__),
    limit_(limit__)
{
}

filter::filter( const where_group_type& where_group__, const order_group_type& order_group__ ) :
    where_group_(where_group__),
    order_group_(order_group__)
{
}

tstring filter::toString()
{
    return wheres_toString() + orders_toString() + limit_toString();
}

tstring filter::wheres_toString()
{
    tstring wheres_string;

    size_t i(0);
    boost::range::for_each( where_group_, [&]( where where_ ) {
        if (i) wheres_string += _T(' ') + where_group_.op( i - 1 );
        wheres_string += _T(" `") + where_.name + _T("` = '") + where_.value + _T('\'');
        i++;
    });

    if (i) wheres_string = _T(" WHERE") + wheres_string;

    return wheres_string;
}

tstring filter::orders_toString()
{
    tstring orders_string;

    bool need_comma(false);
    boost::range::for_each( order_group_, [&]( order_by order_ ) {
        if (need_comma) orders_string += _T(',');
        orders_string += _T(" `") + order_.name + _T("` ") + order_.direction;
        need_comma = true;
    });

    if (need_comma) orders_string = _T(" ORDER BY") + orders_string;

    return orders_string;
}

tstring filter::limit_toString()
{
    using namespace boost;

    tstring limit_string;

    if (-1 != limit_.quantity) limit_string = lexical_cast< tstring >( limit_.quantity );
    if (-1 != limit_.from)     limit_string = lexical_cast< tstring >( limit_.from ) + _T(",") + limit_string;

    if (-1 != limit_.quantity || -1 != limit_.from)
        return _T(" LIMIT ") + limit_string;

    return tstring();
}

} // namespace mysql
