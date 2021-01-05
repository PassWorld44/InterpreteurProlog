#include "complextherm.h"

std::ostream& operator<<(std::ostream& out, const complex_term_decl& co)
{
	for(const std::unique_ptr<Thing>& i : co)
	{
		out << *i;
	}
	return out;
}
