#pragma once

#include <algorithm>
#include <bitset>
#include <cinttypes>
#include <memory>

#include "Parsers/Parser.h"
#include "Rendering/Renderer.h"
#include "Rendering/Surface.h"
#include "Rendering/Texture.h"
#include "System/Logger.h"
#include "System/filesystem.h"

namespace Sourcehold {
namespace Parsers {
namespace TGX {
// Decompresses tgxFile into a image in RGBA8888 format.
//
// Takes a Parser pointing to a .tgx file.
// It is the callers responibility to ensure the validity of the parser.
//
// Returns a tuple of IMAGE_WIDTH , IMAGE_HEIGHT, RGBA8888_DATA.
std::tuple<size_t, size_t, std::vector<uint32_t>> Load(
    Parser& tgxFile) noexcept;

//***********
//**Details**
//***********
namespace details {
// Tgx header format
struct TgxHeader {
  uint32_t width;
  uint32_t height;
};
// Tgx specific command token
enum class Command {
  pixels = 0,
  transparent = 1,
  repeatingPixel = 2,
  newline = 4
};
// Tgx specific command header
struct TgxCommandHeader {
  Command command;
  uint8_t length;
};

TgxHeader GetTgxHeader(Parser& tgxFile) noexcept;
TgxCommandHeader GetTgxCommandHeader(Parser& tgxFile) noexcept;

}  // namespace details
}  // namespace TGX
}  // namespace Parsers
}  // namespace Sourcehold
