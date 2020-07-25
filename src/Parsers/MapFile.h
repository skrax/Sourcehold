#pragma once

#include <cinttypes>

#include "Parsers/Parser.h"
#include "Rendering/Surface.h"
#include "Rendering/Texture.h"
#include "System/filesystem.h"

namespace Sourcehold {
namespace Parsers {

class MapFile : private Parser {
  Rendering::Texture preview;

 public:
  MapFile();
  MapFile(ghc::filesystem::path path);
  MapFile(const MapFile&) = delete;
  ~MapFile();

  bool LoadFromDisk(ghc::filesystem::path path);

  inline Rendering::Texture& GetPreview() {
    return preview;
  }

 protected:
  struct MapSec;
  MapSec BlastSection();
  void ParsePreview();
  uint32_t ComputeCRC32(const void* data, size_t size);
};
}  // namespace Parsers
}  // namespace Sourcehold
