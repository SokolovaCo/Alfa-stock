#include "stdafx.h"

#include "table.hpp"

#include "../query/query.hpp"

#include <boost/range/algorithm/find.hpp>

namespace mysql {

table::table()
{
}

table::table( const tstring& name__ ) :
    name_(name__)
{
}

table::table( const tstring& name__, const header_type& header__ ) :
    name_(name__),
    header_(header__)
{
}

bool table::load( const filter& filter__ )
{
    query load_query( query::select, this, filter__ );

    return load_query.execute_select();
}

bool table::save_insert( const filter& filter__ )
{
    query insert_query( query::insert, this, filter__ );

    return insert_query.execute();
}

bool table::save_update( const filter& filter__ )
{
    query update_query( query::update, this, filter__ );

    return update_query.execute();
}

bool table::delete_( const filter& filter__ )
{
    query delete_query( query::delete_, this, filter__ );

    return delete_query.execute();
}

const tstring& table::getName() const
{
    return name_;
}

table::header_type& table::getHeader()
{
    return header_;
}

void table::setContent( content_type&& content__ )
{
    content_ = std::move( content__ );
}

table::content_type::iterator table::begin()
{
    return content_.begin();
}

table::content_type::iterator table::end()
{
    return content_.end();
}

table::content_type::size_type table::size() const
{
    return content_.size();
}

bool table::empty() const
{
    return content_.empty();
}

void table::clear()
{
    content_.clear();
}

} // namespace mysql
