#pragma once

#ifndef store_hpp__
#define store_hpp__

#include "../types.hpp"


struct Store
{
	Store::Store(){}

	Store::Store(unsigned long long id_s, unsigned id_a, unsigned id_p, bool avail)
		: id_store(id_s)
		, id_article(id_a)
		, id_place(id_p)
		, availability(avail)
	{}


	unsigned long long id_store;
	unsigned id_article;
	unsigned id_place;
	bool availability;
};

#endif