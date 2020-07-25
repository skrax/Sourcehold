#pragma once

#include <cinttypes>
#include <memory>

#include "Parsers/Parser.h"
#include "Rendering/Renderer.h"
#include "Rendering/Texture.h"
#include "Rendering/TextureAtlas.h"
#include "Rendering/Tileset.h"
#include "System/filesystem.h"

namespace Sourcehold {
namespace Parsers {
/**
 * Container format for tiles/animations/images
 * Creates an entry in TextureAtlas for every image collection (Building, unit,
 * etc.) and a Tileset depending on the stored type
 */
class Gm1File : private Parser {
  std::shared_ptr<Rendering::TextureAtlas> textureAtlas;
  std::shared_ptr<Rendering::Tileset> tileset;
  struct ImageHeader;
  struct Gm1Entry;
  struct Gm1Header;

 public:
  Gm1File();
  Gm1File(ghc::filesystem::path path, bool cached = false);
  Gm1File(const Gm1File &) = delete;
  Gm1File &operator=(const Gm1File &) = delete;
  ~Gm1File();

  bool LoadFromDisk(ghc::filesystem::path path, bool cache = false);
  void Free();

  inline std::shared_ptr<Rendering::Tileset> GetTileset() {
    return tileset;
  }
  inline std::shared_ptr<Rendering::TextureAtlas> GetTextureAtlas() {
    return textureAtlas;
  }

 protected:
  const uint32_t MAX_NUM = 2048;
  bool GetImage(uint32_t index, std::vector<Gm1Entry> &entries, char *imgdata,
                Gm1Header *header);
  void ReadPalette();
};
}  // namespace Parsers
}  // namespace Sourcehold
