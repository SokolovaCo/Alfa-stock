#pragma once

#ifndef srtable_hpp__
#define srtable_hpp__

#include "types.hpp"


struct SRTable
{
	SRTable::SRTable(){}

	SRTable::SRTable(unsigned id, tstring n, tstring adr, unsigned id_d)
		: id_n(id)
		, name(n)
		, addr(adr)
		, id_director(id_d)
	{}


	unsigned id_n;
	tstring name;
	tstring addr;
	unsigned id_director;
};

#endif