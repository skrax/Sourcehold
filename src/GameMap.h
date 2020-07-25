#pragma once

#include <cinttypes>
#include <map>
#include <memory>
#include <vector>

#include "Assets.h"
#include "Building.h"
#include "Parsers/MapFile.h"
#include "Rendering/Renderer.h"
#include "Rendering/Tileset.h"
#include "System/filesystem.h"

namespace Sourcehold {
namespace Parsers {
class Gm1File;
class TgxFile;
}  // namespace Parsers
namespace Game {

struct WorldInformation {
  Assets::MapDimension type;
  std::map<Building, bool> unlockedBuildings;
};

class GameMap : public Parsers::MapFile {
  int mult = 1, dim;
  std::shared_ptr<Parsers::Gm1File> gm1_tile;
  std::shared_ptr<Rendering::Tileset> tileset;
  std::vector<SDL_Rect> tiles;

 public:
  GameMap(Assets::MapDimension type);
  GameMap(ghc::filesystem::path path);
  GameMap(const GameMap&) = delete;
  ~GameMap();

  void LoadFromDisk(ghc::filesystem::path path);
  void Render();

 protected:
};
}  // namespace Game
}  // namespace Sourcehold
