#pragma once

#include <string>
#include <iostream>

#include "thing.h"

struct Atom : public Thing
{
	Atom(std::string str_) : Thing{Type::atom}, str{str_} {}
	std::string str;
};

std::ostream& operator<<(std::ostream& output, const Atom& at);