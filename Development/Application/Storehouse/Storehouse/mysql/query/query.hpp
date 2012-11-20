#pragma once
#ifndef query_hpp__
#define query_hpp__

#include "../../types.hpp"
#include "filter/filter.hpp"

namespace mysql {

class table;

class query
{
public:
    enum methods {

        undefined = 0x0,
        select,
        insert,
        update,
        delete_

    };

public:
    query( const methods& method__,
           table* const table__,
           const filter& filter__ );

public:
    bool execute_select();
    bool execute();

private:
    tstring toString();

private:
    methods method_;
    table*  table_;
    filter  filter_;
};

} // namespace mysql

#endif // query_hpp__
