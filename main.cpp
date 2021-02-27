#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <sstream>
#include <functional>

#include "thing/atom.h"
#include "thing/number.h"
#include "thing/variable.h"
#include "thing/complextherm.h"
#include "predicate.h"
#include "listpredicate.h"
#include "trim.h"

void read(std::string::iterator startS, std::string::iterator endS, listPredicate& listDecl)
{
	for(auto it = startS; it != endS; it++)
	//itere sur le programme entre en string
	{
		if(!isalpha(*it) && *it != '_')
		{
			//std::cout << *(it - 1) << " " << *it << " " << *(it + 1) << std::endl; 
			throw std::runtime_error("not a predicate");
		}

		auto endAtom = std::find_if_not(it, endS, [](int c) -> bool {return isalpha(c) || c == '_';});

		auto endParenthesis = std::find_if(endAtom, endS, 
		[](char c) -> bool {return c == ')' || c == '.';});

		int arity = 0;
		if(*endAtom == '(' && !std::string{endAtom, endParenthesis}.empty())
			arity = std::count(endAtom, endParenthesis, ',') + 1;

		const std::string name {it, endAtom};

		//std::cout << listDecl << std::endl;
		//std::cin.get();

		std::stringstream ss;
		ss << name << "/" << arity;

		auto pair = listDecl.try_emplace(ss.str(), name, arity);
		//create or find the corresponding predicate

		//std::cout << "caca:" <<pair.second << " " << listDecl.size()<<std::endl;
		//std::cout << listDecl << std::endl;
		//std::cin.get();

		predicate& pred = *static_cast<predicate*>(&*(*pair.first).second);

		if(arity != 0)
		{
			//---------- Read the parameters of the predicate --------
			std::pair<listThing::iterator, bool> pair2 = pred->emplace(std::make_unique<complex_term_decl>());

			complex_term_decl& listArgs = *(*pair2.first);

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

					//std::cout << listArgs << std::endl;

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
	//std::cout << "." << listDecl << std::endl;
}

void analysInput(std::string txt, const listPredicate& listPred)
{
    listPredicate askList;

	read(txt.begin(), txt.end(), askList);
	//we just have to compare the results now

	if(askList.size() != 1)
	{
		throw std::runtime_error("bad input provided (and not a safe implementation also)");
	}

	predicate& askPred { *askList.begin()->second }; //we only have one element

	auto a = std::find_if(listPred.begin(), listPred.end(), 
		[&](const std::pair<const std::string, const std::unique_ptr<predicate>&> pair) -> bool
	{
		std::cout << pair.second->getFullName() << " " << askPred.getFullName() << std::endl;
		return pair.second->getFullName() == askPred.getFullName();
	});

	complex_term_decl& compl = *(*askPred->begin());

	if(a != listPred.end()) //there are a predicate with the same name and arity
	{
		const predicate& corrPred { *(*a).second };

		auto it = std::find_if(corrPred->begin(), corrPred->end(), 
			[&](const std::unique_ptr<complex_term_decl>& ptr) -> bool {
			return compl == *ptr;
		});	

		if(compl == **it) //perfecly equal, variables aren't needed
		{
			std::cout << "yes" << std::endl;
		}
		else
		{
			std::cout << "not implemented yet" << std::endl;
		}
	}
	else
	{
		std::cout << "no" << std::endl;
	}
}

int main() 
{
	listPredicate listDeclarations;
	//where everithing is stored

	std::ifstream file{"prog.txt", std::ifstream::in};
	std::string fileTxt;
	std::string line;
	while(file >> line)
	{
		fileTxt.append(line);
	}

	read(fileTxt.begin(), fileTxt.end(), listDeclarations);

	std::cout << fileTxt << std::endl;

	std::string lastInput;
	std::string totalinput;

	bool is_continuing {true};
	while(is_continuing && totalinput != "quit")
	{
		bool findPoint {false};
		lastInput.clear();
		totalinput.clear();

		std::cout << "?- ";

		while(!findPoint)
		{
			lastInput.clear();

			std::getline(std::cin, lastInput);
			lastInput = trim(lastInput);
			totalinput.append(lastInput);

			if(std::find(lastInput.begin(), lastInput.end(), '.') != lastInput.end())
			{
				findPoint = true;
			}

			if(lastInput == "quit")
			{
				is_continuing = false;
				break;
			}

			//std::cout << lastInput << std::endl;
			//std::cout << totalinput << std::endl;
		}

		if(is_continuing) //otherwise just quit and don't analyse le last thing entered
		{
			analysInput(totalinput, listDeclarations);
		}

		std::cin.clear();
	}
}