#pragma once

#include <string>
#include <vector>
#include <type_traits>
#include <exception>
#include <iostream>
#include <sstream>
#include <unordered_set>
#include <set>
#include <memory>

#include "thing.h"
#include "number.h"
#include "variable.h"
#include "atom.h"

#include "../trash.h"

class complex_term_decl : public Thing, public std::vector<std::unique_ptr<Thing>>
{
public:
	complex_term_decl() : Thing{Type::complex_term_decl}
	{}
};

std::ostream& operator<<(std::ostream& out, const complex_term_decl& co);
