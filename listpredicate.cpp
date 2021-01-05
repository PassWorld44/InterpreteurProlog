#include "listpredicate.h"

std::ostream& operator<<(std::ostream& output, const listPredicate& liste)
{
	for(const auto& pair : liste)
	{
		output << pair.second << std::endl;
	}
	return output;
}