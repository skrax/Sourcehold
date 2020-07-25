#pragma once

#include <SDL.h>

#include <cinttypes>
#include <memory>

#include "Rendering/Renderer.h"
#include "Rendering/Surface.h"
#include "Rendering/Texture.h"

namespace Sourcehold {
namespace Rendering {
/*
 * Constructs a tileset from a GM1 container
 */
class Tileset : public Texture {
  uint32_t numRows, num;
  Surface surf;

 public:
  Tileset();
  ~Tileset();

  void Allocate(uint32_t num);
  void Create();
  void SetTile(Texture &image, uint32_t index);
  void Clear();
  Uint32 *GetData();
  void Lock();
  void Unlock();

  inline uint32_t GetNumTiles() {
    return num;
  }
  inline Surface &GetSurface() {
    return surf;
  }
  SDL_Rect GetTile(uint32_t index);

 protected:
  std::pair<uint32_t, uint32_t> IndexToCoords(uint32_t index);
};
}  // namespace Rendering
}  // namespace Sourcehold
