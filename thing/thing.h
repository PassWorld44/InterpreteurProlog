#pragma once

#include <iostream>

struct Thing
{
	enum Type {atom, variable, number, complex_term_decl};

	Type t;

	bool operator==(Thing other);
};

std::ostream& operator<<(std::ostream& o, const Thing::Type&);