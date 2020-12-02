#include "listthing.h"

#include "thing/complextherm.h"
//multi inclusion

bool EqualityThing::operator()(const std::unique_ptr<Thing>& lhs, const std::unique_ptr<Thing>& rhs) const
   {
    if((*lhs.get()).t == (*rhs.get()).t) //the same type
    {
        switch ((*lhs.get()).t)
        {
        case Thing::Type::atom:
            return *static_cast<Atom*>(rhs.get()) == *static_cast<Atom*>(lhs.get());
            break;
        case Thing::Type::predicate:
			return *static_cast<predicate*>(rhs.get()) == *static_cast<predicate*>(lhs.get());
            break;
        case Thing::Type::variable:
            return *static_cast<Variable*>(rhs.get()) == *static_cast<Variable*>(lhs.get());
            break;
        case Thing::Type::number:
            return *static_cast<Number*>(rhs.get()) == *static_cast<Number*>(lhs.get());
            break;
		case Thing::Type::complex_term_decl:
			return *static_cast<complex_term_decl*>(rhs.get()) == *static_cast<complex_term_decl*>(lhs.get());
			break;
        }
    }
    else
	{
        return false;
    }
}

std::ostream& operator<<(std::ostream& output, const listThing& ls)
{
	for(const std::unique_ptr<Thing>& element : ls)
	{
		output << *element << std::endl;
	}

	return output;
}