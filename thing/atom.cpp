#include "atom.h"

std::ostream& operator<<(std::ostream& output, const Atom& at)
{
	output << at.str;
	return output;
}
