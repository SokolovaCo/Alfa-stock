#pragma once

#ifndef dstable_hpp__
#define dstable_hpp__

#include "types.hpp"
#include <boost/date_time.hpp>

struct DSTable
{
	DSTable::DSTable(){}

	DSTable::DSTable(unsigned id_, boost::posix_time::ptime dt, unsigned long long id_i, unsigned id_a)
		: id(id_)
		, datetime(dt)
		, id_item(id_i)
		, id_agent(id_a)
	{}


	unsigned id;
	boost::posix_time::ptime datetime;
	unsigned long long id_item;
	unsigned id_agent
};

#endif