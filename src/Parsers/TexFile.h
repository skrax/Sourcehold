#pragma once

#include <cinttypes>
#include <map>
#include <vector>

#include "Assets.h"
#include "Parsers/Parser.h"
#include "System/filesystem.h"

namespace Sourcehold {
namespace Parsers {
class TexFile : private Parser {
 public:
  TexFile();
  ~TexFile(){};

  bool LoadFromDisk(ghc::filesystem::path path);

  std::wstring &GetString(Assets::TextSection sec, uint16_t index);

 protected:
  std::map<Assets::TextSection, std::vector<std::wstring>> strings;
  std::wstring dummy_text = L"Text not found";
};
}  // namespace Parsers
}  // namespace Sourcehold
