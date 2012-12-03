#pragma once

#ifndef place_hpp__
#define place_hpp__

#include "types.hpp"


struct Place
{
	Place::Place(){}

	Place::Place(unsigned id_p, unsigned l, unsigned p)
		: id_place(id_p)
		, line(l)
		, point(p)
	{}


	unsigned id_place;
	unsigned line;
	unsigned point;
};

#endif