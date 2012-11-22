#include "stdafx.h"

#include "query.hpp"

#include "../table/table.hpp"
#include "../mysql.hpp"

#include <boost/range/algorithm/for_each.hpp>

namespace mysql {

query::query( const methods& method__,
              table* const table__,
              const filter& filter__ ) :
    method_(method__),
    table_(table__),
    filter_(filter__)
{
}

bool query::execute_select()
{
    if (!mysql::instance().isConnected())
        return false;

    table_->setContent( mysql::instance().execute_query_select( this->toString() ) );

    return true;
}

bool query::execute()
{
    if (!mysql::instance().isConnected())
        return false;

    mysql::instance().execute_query( this->toString() );

    return true;
}

tstring query::toString()
{
    tstring query_string, db_string;

	db_string =  _T(" `");
	db_string += _DB_;
	db_string += _T("`.`");

    switch (method_)
    {
    case select:
        {
            query_string = _T("SELECT");

            bool need_comma(false);
            boost::range::for_each( table_->getHeader(), [&]( table::header_field field_ ) {
                if (need_comma) query_string += _T(',');
                                query_string += _T(" `") + field_.value() + _T('`');
                need_comma = true;
            });

            // small hack, we no need new variable
            if (!need_comma) query_string += _T("*");

            query_string += _T(" FROM") + db_string + table_->getName() + _T('`');
        }
        break;

    case insert:
        {
            query_string = _T("INSERT INTO `") + table_->getName() + _T("` ");

            bool need_bracket(true);
            bool need_comma(false);
            boost::range::for_each( table_->getHeader(), [&]( table::header_field field_ ) {
                if (need_bracket) query_string += _T('(');
                if (need_comma)   query_string += _T(", ");
                                  query_string += _T('`') + field_.value() + _T('`');
                need_bracket = false;
                need_comma   = true;
            });

            if (!need_bracket) query_string += _T(") ");

            query_string += _T("VALUES (");

            need_comma   = false;
            for (auto it = table_->begin()->begin(), end = table_->begin()->end(); it != end; ++it)
            {
                if (need_comma) query_string += _T(',');
                                query_string += _T(" '") + it->any_value< tstring >() + _T('\'');
                need_comma = true;
            }

            query_string += _T(')');
        }
        break;

    case update:
        {
            query_string = _T("UPDATE `") + table_->getName() + _T("` SET");

            auto it = table_->begin()->begin();

            bool need_comma(false);
            boost::range::for_each( table_->getHeader(), [&]( table::header_field field_ ) {
                if (need_comma) query_string += _T(',');
                                query_string += _T(" `") + field_.value() + _T('`');
                                query_string += _T("='") + it->any_value< tstring >() + _T('\'');
                need_comma = true;
                ++it;
            });
        }
        break;

    case delete_:
        {
            query_string = _T("DELETE FROM `") + table_->getName() + _T('`');
        }
        break;
    }

    return query_string + filter_.toString() + _T(';');
}

} // namespace mysql
