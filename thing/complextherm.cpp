#include "complextherm.h"

bool EqualityThing::operator()(const std::unique_ptr<Thing>& lhs, const std::unique_ptr<Thing>& rhs) const
{
	std::cout << "operator(unique<Thing>, unique<Thing>)" << std::endl; 

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
	std::cout << ls.size() << std::endl;
	for(const std::unique_ptr<Thing>& element : ls)
	{
		output << *element << std::endl;
	}

	return output;
}

predicate::predicate(std::string str_, int arity_) : Thing{Thing::predicate}, arity{arity_}, str{str_}
{}

bool predicate::operator==(const predicate& other) const
{
	//std::cout << "? " << getFullName() << std::endl << other.getFullName() << std::endl << (getFullName() == other.getFullName()) << std::endl << std::endl;

	return (getFullName() == other.getFullName());
}

std::string predicate::getName() const
{
	return str;
}

std::string predicate::getFullName() const
{
	std::stringstream ss;
	ss << getName() << "/" << getArity();

	return ss.str();
}

int predicate::getArity() const
{
	return arity;
}

std::ostream& operator<<(std::ostream& outpout, const predicate& pred)
{
	//std::cout << "i'm in";
	outpout << pred.getFullName();
	
	if(pred.getArity() != 0)
		outpout << " : (" << pred.size() << ")"; 
	
	outpout << std::endl;

	for(const std::unique_ptr<Thing>& i : pred)
	{
		outpout << "-" << *i << std::endl;
	}

	return outpout;
}

std::ostream& operator<<(std::ostream& out, const complex_term_decl& co)
{
	for(const std::unique_ptr<Thing>& i : co)
	{
		out << *i;
	}
	return out;
}
