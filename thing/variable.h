#pragma once

#include <iostream>

#include "thing.h"

struct Variable : public Thing
{
	Variable(std::string str_) : Thing{Type::variable}, str{str_} {}
	std::string str;
};
