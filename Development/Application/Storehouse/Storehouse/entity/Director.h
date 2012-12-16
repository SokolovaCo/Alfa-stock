#pragma once

#ifndef director_hpp__
#define director_hpp__

#include "../types.hpp"


struct Director
{
	Director::Director(){}

	Director::Director(unsigned id, tstring sr, tstring n, tstring p)
		: id_director(id)
		, surname(sr)
		, name(n)
		, patronymic(p)
	{}


	unsigned id_director;
	tstring surname;
	tstring name;
	tstring patronymic;
};

#endif