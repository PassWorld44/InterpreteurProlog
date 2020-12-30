#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <unordered_set>

#include "thing/atom.h"
#include "thing/number.h"
#include "thing/variable.h"
#include "thing/complextherm.h"

#include "thing/listthing.h"

void read(std::string::iterator startS, std::string::iterator endS, listThing& listDecl)
{
	for(auto it = startS; it != endS; it++)
	{
		std::cout << *it << std::endl;

		if(!isalpha(*it) && *it != '_')
		{
			std::cout << *(it - 1) << " " << *it << " " << *(it + 1) << std::endl; 
			throw std::runtime_error("not a predicate");
		}

		auto endAtom = std::find_if_not(it, endS, [](int c) -> bool {return isalpha(c) || c == '_';});

		auto endParenthesis = std::find_if(endAtom, endS, 
		[](char c) -> bool {return c == ')' || c == '.';});

		int arity = std::count(endAtom, endParenthesis, ',');
		std::string name {it, endAtom};
		std::cout << name << std::endl;

		auto tuple = listDecl.insert(std::make_unique<predicate>(name, arity));
		//create or find the corresponding complex_term

		predicate& pred = *static_cast<predicate*>( &(*(*tuple.first)) );

		//---------- Read the parameters of the predicate --------
		auto tuple2 = pred.emplace(std::make_unique<complex_term_decl>());

		complex_term_decl& listArgs = *static_cast<complex_term_decl*>((*tuple2.first).get());

		if(*it == '(')
		{
			it++;
			while(it != endParenthesis)
			{
				auto endWord = std::find_if(it, endParenthesis, [](char c) -> bool {return isalpha(c);});
				listArgs.emplace_back(std::make_unique<Atom>(std::string{it, endWord}));
			}
		}

		it = endParenthesis;

		if(*(it+1)=='.')
		{
			it++;
		}

		std::cout << "." << listDecl << std::endl;
	}
}

int main() 
{
	listThing listDeclarations;

	std::ifstream file{"prog.txt", std::ifstream::in};

	std::string fileTxt;

	std::string line;
	while(file >> line)
	{
		fileTxt.append(line);
	}

	read(fileTxt.begin(), fileTxt.end(), listDeclarations);

	std::cout << fileTxt << std::endl;
}