#include "thing.h"

bool Thing::operator==(Thing other)
{ 
	return t == other.t;
}

std::ostream& operator<<(std::ostream& o, const Thing::Type& t)
{
	switch(t)
	{
	case Thing::atom:
		o << "atom";
		break;
	case Thing::variable:
		o << "variable";
		break;
	case Thing::number:
		o << "number";
		break;
	case Thing::complex_term_decl:
		o << "complex_term_decl";
		break;
	}

	return o;
}