#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <functional>
#include <memory>

#include "predicate.h"

using listPredicate = std::unordered_map<std::string, std::unique_ptr<predicate>>;
using listWPredicate = std::unordered_map<std::string, std::reference_wrapper<predicate>>;

std::ostream& operator<<(std::ostream& output, const listWPredicate&);