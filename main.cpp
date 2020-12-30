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

void read(std::string::iterator startS, std::string::iterator endS, listThing& listDecl)
{
	for(auto it = startS; it != endS; it++)
	{
		if(!isalpha(*it) && *it != '_')
		{
			std::cout << *(it - 1) << " " << *it << " " << *(it + 1) << std::endl; 
			throw std::runtime_error("not a predicate");
		}

		auto endAtom = std::find_if_not(it, endS, [](int c) -> bool {return isalpha(c) || c == '_';});

		auto endParenthesis = std::find_if(endAtom, endS, 
		[](char c) -> bool {return c == ')' || c == '.';});

		int arity = 0;
		if(*endAtom == '(' && !std::string{endAtom, endParenthesis}.empty())
			arity = std::count(endAtom, endParenthesis, ',') + 1;

		std::string name {it, endAtom};

		std::cout << listDecl << std::endl;

		std::cin.get();

		std::unique_ptr<Thing> ptr {std::make_unique<predicate>(name, arity) };

		std::pair<listThing::iterator, bool> pair = listDecl.insert(std::move(ptr));
		//create or find the corresponding complex_term

		//std::cout << "caca:" <<pair.second << " " << listDecl.size()<<std::endl;

		std::cout << listDecl << std::endl;

		std::cin.get();

		predicate& pred = *static_cast<predicate*>(&(*(*pair.first)));

		if(arity != 0)
		{
			//---------- Read the parameters of the predicate --------
			std::pair<listThing::iterator, bool> pair2 = pred.emplace(std::make_unique<complex_term_decl>());

			complex_term_decl& listArgs = *static_cast<complex_term_decl*>((*pair2.first).get());

			it = endAtom;

			if(*it == '(')
			{
				it++;
				while(it != endParenthesis)
				{
					auto endWord = std::find_if(it, endParenthesis, [](char c) -> bool {return c == ' ' || c == ',';});

					std::string strAtom {it, endWord};
					//std::cout << strAtom << std::endl;

					listArgs.emplace_back(std::make_unique<Atom>(strAtom));

					std::cout << listArgs << std::endl;

					it = endWord;
				}
			}
		}

		it = endParenthesis;

		if(*(it+1)=='.')
		{
			it++;
		}

		
	}
	std::cout << "." << listDecl << std::endl;
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