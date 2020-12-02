#pragma once

struct Thing
{
	enum Type {atom, variable, number, predicate, complex_term_decl};

	Type t;

	bool operator==(Thing other);
};