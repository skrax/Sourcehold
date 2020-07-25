#include "Parsers/MlbFile.h"

namespace Sourcehold {
namespace Parsers {
namespace Mlb {
std::vector<std::string> Load(Parser& mlb) {
  auto number_of_entries = mlb.Get<uint16_t>();
  std::vector<std::string> result(number_of_entries);

  std::generate(result.begin(), result.end(), [&] {
    // TODO(skrax): Header does not match description on the wiki
    // Seems to work ok
    // Unknowns
    mlb.Get<uint32_t>();
    mlb.Get<uint32_t>();
    mlb.Get<uint32_t>();
    mlb.Get<uint16_t>();

    // Read entry
    auto len = mlb.Get<uint32_t>();

    auto description = mlb.Get<uint16_t>(len);
    return std::string(description.begin(), description.end());
  });

  return result;
}
}  // namespace Mlb
}  // namespace Parsers
}  // namespace Sourcehold

