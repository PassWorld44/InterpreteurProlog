#pragma once

#include <unordered_map>
#include <string>
#include <iostream>

#include "predicate.h"

using listPredicate = std::unordered_map<std::string, predicate>;

std::ostream& operator<<(std::ostream& output, const listPredicate&);