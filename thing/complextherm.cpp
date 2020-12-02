#include "complextherm.h"

predicate::predicate(std::string str_, int arity_) :  arity{arity_}, str{str_}
{}

bool predicate::operator==(const predicate& other) const
{
	return (str == other.str && arity == other.arity);
}

std::string predicate::getName() const
{
	return str;
}

int predicate::getArity() const
{
	return arity;
}

std::ostream& operator<<(std::ostream& outpout, const predicate& pred)
{
	outpout << pred.getName() << " /" << pred.getArity() << " :" << std::endl;

	for(const std::unique_ptr<Thing>& i : pred)
	{
		outpout << "-\t" << *i << std::endl;
	}

	return outpout;
}