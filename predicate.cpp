#include "predicate.h"

template<>
bool std::equal_to<std::unique_ptr<complex_term_decl>>::operator()
	(const  std::unique_ptr<complex_term_decl>& lhs, const  std::unique_ptr<complex_term_decl>& rhs) const noexcept
{
	return *lhs == *rhs;
}


std::ostream& operator<<(std::ostream& output, const listThing& ls)
{
	//std::cout << ls.size() << std::endl;
	for(const std::unique_ptr<complex_term_decl>& element : ls)
	{
		output << *element << std::endl;
	}

	return output;
}

predicate::predicate(std::string str_, int arity_) : arity{arity_}, str{str_}
{}

predicate::predicate(std::pair<std::string, int> data) : arity{data.second}, str{data.first}
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

	for(const std::unique_ptr<complex_term_decl>& i : pred)
	{
		outpout << "-" << *i << std::endl;
	}

	return outpout;
}