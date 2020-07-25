#pragma once

#include <fstream>
#include <vector>

#include "Assets.h"
#include "Parsers/Parser.h"

namespace Sourcehold {
namespace Parsers {
namespace Mlb {
// Takes a parser pointing to a .mlb file.
// It is the callers responsibility to check if the parser is valid to read
// from.
//
// Returns all entries of a .mlb file as strings.
std::vector<std::string> Load(Parser& mlb) noexcept;
}  // namespace Mlb
}  // namespace Parsers
}  // namespace Sourcehold
