#include "listpredicate.h"

std::ostream& operator<<(std::ostream& output, const listWPredicate& liste)
{
	for(const auto& pair : liste)
	{
		output << pair.second << std::endl;
	}
	return output;
}