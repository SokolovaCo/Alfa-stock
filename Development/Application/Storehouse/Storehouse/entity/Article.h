#pragma once

#ifndef article_hpp__
#define article_hpp__

#include "../types.hpp"


struct Article
{
	Article::Article(){}

	Article::Article(unsigned id_n, tstring n, unsigned id_f, unsigned id_st, double p, float s, unsigned id_u)
		: id(id_n)
		, name(n)
		, id_firm(id_f)
		, id_subtype(id_st)
		, price(p)
		, size(s)
		, id_unit(id_u)
	{}


	unsigned id;
	tstring name;
	unsigned id_firm;
	unsigned id_subtype;
	double price;
	float size;
	unsigned id_unit;
};

#endif