#pragma once

#include <algorithm>
#include <chrono>
#include <cinttypes>
#include <cstdlib>
#include <memory>

#include "Audio/Song.h"
#include "Events/Event.h"
#include "Events/Mouse.h"
#include "GUI/MenuUtils.h"
#include "GUI/UIState.h"
#include "GameManager.h"
#include "Parsers/AniFile.h"
#include "Parsers/Gm1File.h"
#include "Parsers/TgxFile.h"
#include "Rendering/BinkVideo.h"
#include "Rendering/Texture.h"
#include "Rendering/TextureAtlas.h"

namespace Sourcehold {
namespace Game {
/**
 * Handles non game states - menus and intro sequence
 */
class Startup : protected EventConsumer<Mouse> {
 public:
  Startup();
  Startup(const Startup &) = delete;
  ~Startup();

  void PlayMusic();
  GUI::UIState Begin();

 protected:
  void onEventReceive(Mouse &event) override;

  double startTime = 0.0;
  Audio::Song aud_startup;

  /* Resources */
  std::shared_ptr<TgxFile> tgx_firefly, tgx_taketwo, tgx_present, tgx_logo,
      tgx_firefly_front;
  std::shared_ptr<BinkVideo> intro;

  enum StartupSequence : uint8_t {
    STARTUP_FIREFLY_LOGO = 0,
    STARTUP_TAKETWO_LOGO,
    STARTUP_PRESENT,
    STARTUP_STRONGHOLD_LOGO,
    STARTUP_MULTIPLAYER_INFO,
    STARTUP_INTRO
  };

  GUI::UIState currentUIState = GUI::UIState::INTRO_SEQUENCE;
  uint8_t currentStartupState = 0;
};
}  // namespace Game
}  // namespace Sourcehold
