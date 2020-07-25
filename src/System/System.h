#pragma once

#include <cinttypes>
#include <string>

#include "Rendering/Renderer.h"

namespace Sourcehold {
namespace System {
enum StrongholdEdition {
  STRONGHOLD_CLASSIC,
  STRONGHOLD_COLLECTION,
  STRONGHOLD_HD
};

/**
 * Game startup options, modified via config file
 * or command line arguments
 */
struct GameOptions {
  std::string config;
  std::string dataDir;
  bool debug = false;
  bool noborder = false;
  bool fullscreen = false;
  bool nothread = false;
  bool nosound = false;
  bool nograb = false;
  bool nocache = false;
  bool skip = false;
  int color = -1;
  int width, height;
  uint16_t ndisp;
};
}  // namespace System
}  // namespace Sourcehold
