#pragma once

#ifndef simpletable_hpp__
#define simpletable_hpp__

#include "types.hpp"


struct SimpleTable
{
	SimpleTable::SimpleTable(){}

	SimpleTable::SimpleTable(unsigned id_n, tstring n)
		: id(id_n)
		, name(n)
	{}


	unsigned id;
	tstring name;
};

#endif