#pragma once

#ifndef subtype_hpp__
#define subtype_hpp__

#include "types.hpp"


struct Subtype
{
	Subtype::Subtype(){}

	Subtype::Subtype(unsigned id_s, tstring st, unsigned id_t)
		: id(id_s)
		, name(st)
		, id_type(id_t)
	{}


	unsigned id;
	tstring name;
	unsigned id_type;
};

#endif