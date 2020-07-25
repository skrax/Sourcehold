#include <Parsers/TgxFile.h>
#include <SDL2/SDL_timer.h>
#include <gtest/gtest.h>
#include <util/sdl_helpers.h>

#include <cstdlib>
#include <ios>

#include "Rendering/Display.h"

constexpr auto pathToTgx = "../data/gfx/frontend_loading.tgx";
constexpr auto modeRead = std::ios_base::in | std::ios_base::binary;
constexpr auto modeWrite = std::ios_base::out | std::ios_base::binary;
constexpr auto modeRW = modeRead | std::ios_base::out;
TEST(TgxTest, ReadTgxHeader) {
  using namespace Sourcehold::Parsers;
  Parser parser(pathToTgx, modeRead);
  auto header = TGX::details::GetTgxHeader(parser);
  // DISCLAIMER
  // THE EXPECTED VALUES OF THE TGX HAVE BEEN VERIFIED MANUALLY
  // USE A HEX EDITOR TO REPLICATE THE TEST
  EXPECT_EQ(header.width, 1024);
  EXPECT_EQ(header.height, 768);
}
TEST(TgxTest, ReadTgxCommandHeader) {
  using namespace Sourcehold::Parsers;
  Parser parser(pathToTgx, modeRead);

  auto header = TGX::details::GetTgxHeader(parser);
  auto command = TGX::details::GetTgxCommandHeader(parser);
  // DISCLAIMER
  // THE EXPECTED VALUES OF THE TGX HAVE BEEN VERIFIED MANUALLY
  // USE A HEX EDITOR TO REPLICATE THE TEST
  EXPECT_EQ(command.command, TGX::details::Command::pixels);
  EXPECT_EQ(command.length, 1);
}

TEST(TgxTest, LoadingScreen) {
  using namespace Sourcehold::Parsers;

  Parser parser(pathToTgx, modeRead);

  SDL_Surface* image = nullptr;
  SDL_Surface* screen = nullptr;
  SDL_Window* window = nullptr;

  SDL_Init(SDL_INIT_VIDEO);

  // Load Image
  auto [tgx_width, tgx_height, pixel_data] = TGX::LoadTgxAsRGBA8888(parser);

  // Allocate SDL_Surface and Window
  SurfaceUniquePtr surface(SDL_CreateRGBSurfaceWithFormatFrom(
      pixel_data.data(), tgx_width, tgx_height, 32, tgx_width * 4,
      SDL_PIXELFORMAT_RGBA8888));

  WindowUniquePtr win(
      SDL_CreateWindow("frontend_loading.tgx", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, tgx_width, tgx_height, 0));

  image = surface.get();
  window = win.get();
  screen = SDL_GetWindowSurface(win.get());

  SDL_BlitSurface(image, nullptr, screen, nullptr);
  SDL_UpdateWindowSurface(window);
  while (true) {
    // Get the next event
    SDL_Event event;
    if (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        // Break out of the loop on quit
        break;
      }
    }
  }
  SDL_Quit();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
