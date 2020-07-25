#include "Parsers/TgxFile.h"

#include <ios>

namespace Sourcehold {
namespace Parsers {
namespace TGX {

std::tuple<size_t, size_t, std::vector<uint32_t>> LoadTgxAsRGBA8888(
    Parser &tgx_file) noexcept {
  using namespace details;
  auto tgx_header = GetTgxHeader(tgx_file);

  std::vector<uint32_t> pixel_data(tgx_header.width * tgx_header.height, 0);
  // Pixelformat = SDL_ARGB1555

  auto ToRGBA8888 = [&](uint16_t pixel) -> uint32_t {  //
    uint8_t a = 0xFF;
    uint8_t r = ((pixel >> 10) & 0x1F) << 3;
    uint8_t g = ((pixel >> 5) & 0x1F) << 3;
    uint8_t b = (pixel & 0x1F) << 3;
    return r << 24 | g << 16 | b << 8 | a;
  };
  int pixel_count = 0;
  for (auto line = 0; line < tgx_header.height;) {
    auto command_header = GetTgxCommandHeader(tgx_file);
    switch (command_header.command) {
      case Command::pixels: {
        for (auto i = 0; i < command_header.length; ++i) {
          pixel_data[line * tgx_header.width + pixel_count] =
              ToRGBA8888(tgx_file.Get<uint16_t>());
          ++pixel_count;
        }
        break;
      }
      case Command::transparent: {
        pixel_count += command_header.length;
        break;
      }
      case Command::repeatingPixel: {
        auto pixel = ToRGBA8888(tgx_file.Get<uint16_t>());
        for (auto i = 0; i < command_header.length; ++i) {
          pixel_data[line * tgx_header.width + pixel_count] = pixel;
          ++pixel_count;
        }
        break;
      }
      case Command::newline: {
        ++line;
        pixel_count = 0;
        break;
      }
    }
  }
  return {tgx_header.width, tgx_header.height, pixel_data};
}
namespace details {

TgxHeader GetTgxHeader(Parser &tgxFile) noexcept {
  return {tgxFile.Get<uint32_t>(), tgxFile.Get<uint32_t>()};
}
TgxCommandHeader GetTgxCommandHeader(Parser &tgxFile) noexcept {
  uint8_t rawCommandHeader = tgxFile.Get<uint8_t>();
  Command command = static_cast<Command>(rawCommandHeader >> 5);
  uint8_t length = (rawCommandHeader & uint8_t{0x1F}) + 1;
  return {command, length};
}
}  // namespace details
}  // namespace TGX
}  // namespace Parsers
}  // namespace Sourcehold
