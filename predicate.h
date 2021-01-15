#pragma once

#include <memory>
#include <string>
#include <iostream>
#include <utility>

#include "thing/thing.h"
#include "thing/atom.h"
#include "thing/complextherm.h"
#include "thing/number.h"
#include "thing/variable.h"

struct predicate;

template <>
struct std::equal_to<std::unique_ptr<complex_term_decl>> 
{
	using Type = std::unique_ptr<complex_term_decl>;

  	bool operator()(const Type& thing1, const Type& thing2) const noexcept
	{
		return *thing1 == *thing2;
	}
};

using listThing = std::unordered_set<std::unique_ptr<complex_term_decl>>;

std::ostream& operator<<(std::ostream& output, const listThing& ls);

struct predicate : public listThing
{
	predicate(std::string str_, int arity_);
	predicate(std::pair<std::string, int> data);

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