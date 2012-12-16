#pragma once

#ifndef dstable_hpp__
#define dstable_hpp__

#include "../types.hpp"
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
	unsigned id_agent;

	const tstring GetDateTime() const
	{
		if (datetime.is_not_a_date_time())
			return _T(" ");

		using namespace boost::gregorian;
		using namespace boost::posix_time;

		std::wostringstream stream;
		stream.imbue( std::locale(std::cout.getloc(), new wtime_facet(_T("%Y-%m-%d %H:%M:%S"))) );
		stream << datetime;

		return stream.str();
	}
};

#endif