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

void read(std::string::iterator startS, std::string::iterator endS, listPredicate& listDecl)
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

		const std::string name {it, endAtom};

		//std::cout << listDecl << std::endl;
		//std::cin.get();

		std::stringstream ss;
		ss << name << "/" << arity;

		std::pair<listPredicate::iterator, bool> pair = listDecl.try_emplace(ss.str(),name, arity);
		//create or find the corresponding complex_term

		//std::cout << "caca:" <<pair.second << " " << listDecl.size()<<std::endl;
		//std::cout << listDecl << std::endl;
		//std::cin.get();

		predicate& pred = *static_cast<predicate*>(&(*pair.first).second);

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
    listPredicate askPred;

	read(txt.begin(), txt.end(), askPred);
	//we just have to compare the results now

	for(std::pair<const std::string, predicate>& i : askPred)
	{
		std::find_if(listPred.begin(), listPred.end(), 
			[&](const std::pair<const std::string, const predicate&> pair) -> bool
		{
			return pair.second.getFullName() == i.second.getFullName();
		});
	}
}

int main() 
{
	listPredicate listDeclarations;

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

	bool continue {true};

	while(continue && totalinput != "quit")
	{
		bool findPoint {false};
		lastInput.clear();
		totalinput.clear();

		std::cout << "?- ";

		while(!findPoint)
		{
			lastInput.clear();

			std::getline(std::cin, lastInput);
			totalinput.append(lastInput);

			if(std::find(lastInput.begin(), lastInput.end(), '.') != lastInput.end())
			{
				findPoint = true;
			}

			if(lastInput == "quit")
			{
				continue = true;
				break;
			}

			//std::cout << lastInput << std::endl;
			//std::cout << totalinput << std::endl;
		}

		if(continue) //otherwise just quit and don't analyse le last thing entered
			analysInput(totalinput, listDeclarations);

		std::cin.clear();
	}
}