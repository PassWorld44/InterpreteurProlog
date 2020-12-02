#pragma once

#include <iostream>

#include "thing.h"

struct Number : public Thing
{
	Number(int data_) : Thing{Type::number}, data{data_} {}
	int data;
};

inline std::ostream& operator<<(std::ostream& output, const Number& nb)
{
	output << nb.data;
	return output;
}