#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <exception>
#include <iostream>
<<<<<<< HEAD

#include "thing.h"
#include "listthing.h"
=======
#include <sstream>
#include <unordered_set>
#include <set>
#include <memory>

#include "thing.h"
#include "number.h"
#include "variable.h"
#include "atom.h"

#include "../trash.h"

struct predicate;

struct EqualityThing
{
	bool operator()(const std::unique_ptr<Thing>& lhs, const std::unique_ptr<Thing>& rhs) const;
};

using listThing = std::unordered_set<std::unique_ptr<Thing>, std::hash<std::unique_ptr<Thing>>, EqualityThing>;

std::ostream& operator<<(std::ostream& output, const listThing& ls);
>>>>>>> 2f7c4676f8cffc4a1f61dc6e78b5e93d95d8df48

struct predicate : public Thing, public listThing
{
	predicate(std::string str_, int arity_);

	predicate(predicate&) = delete;
	//we have a unique_ptr for a reason

	bool operator==(const predicate& other) const;
	//we have only one term existing having the same name and arity

	std::string getName() const;
	std::string getFullName() const;

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

std::ostream& operator<<(std::ostream& out, const complex_term_decl& co);
