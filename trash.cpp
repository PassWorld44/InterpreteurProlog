#include "trash.h"

#include "thing/atom.h"
#include "thing/number.h"
#include "thing/variable.h"
#include "thing/complextherm.h"

std::ostream& operator<<(std::ostream& output, const Thing& th)
{
	//std::cout << th.t;
	switch(th.t)
	{
	case Thing::Type::atom:
		output << *static_cast<const Atom*>(&th);
		break;
	case Thing::Type::variable:
		output << *static_cast<const Variable*>(&th);
		break;
	case Thing::Type::number:
		output << *static_cast<const Number*>(&th);
		break;
	case Thing::Type::predicate:
		output << *static_cast<const predicate*>(&th);
		break;
	case Thing::Type::complex_term_decl:
		output << *static_cast<const complex_term_decl*>(&th);
		break;
	}
	return output;
}