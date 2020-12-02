#pragma once

#include <unordered_set>
#include <set>
#include <memory>
#include <exception>
#include <iostream>

#include "thing/thing.h"
#include "thing/number.h"
#include "thing/variable.h"
#include "thing/atom.h"

#include "trash.h"

struct EqualityThing
{
	bool operator()(const std::unique_ptr<Thing>& lhs, const std::unique_ptr<Thing>& rhs) const;
};

using listThing = std::unordered_set<std::unique_ptr<Thing>, std::hash<std::unique_ptr<Thing>>, EqualityThing>;

std::ostream& operator<<(std::ostream& output, listThing& ls);