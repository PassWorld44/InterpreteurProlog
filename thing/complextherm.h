#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <exception>
#include <iostream>


#include "thing.h"
#include "../listthing.h"

struct predicate : public Thing, public listThing
{
	predicate(std::string str_, int arity_);

	predicate(predicate&) = delete; 
	//we have a unique_ptr for a reason

	bool operator==(const predicate& other) const;
	//we have only one term existing having the same name and arity

	std::string getName() const;
	int getArity() const;

private:

	std::string str;
	int arity;
};

std::ostream& operator<<(std::ostream& outpout, const predicate& pred);

class complex_term_decl : public Thing, public std::vector<std::unique_ptr<Thing>>
{
public:
	complex_term_decl() : Thing{Type::complex_term_decl}
	{}
};
