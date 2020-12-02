#pragma once

#include <string>
#include <iostream>

#include "thing.h"

struct Atom : public Thing
{
	Atom(std::string str_) : Thing{Type::atom}, str{str_} {}
	std::string str;
};

inline std::ostream& operator<<(std::ostream& output, const Atom& at)
{
	output << at.str;
	return output;
}
