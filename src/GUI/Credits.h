#pragma once

#include <cinttypes>
#include <memory>

#include "Audio/Song.h"
#include "Events/Event.h"
#include "Events/Mouse.h"
#include "GUI/Layout.h"
#include "GameManager.h"
#include "Parsers/HlpFile.h"
#include "Parsers/TgxFile.h"
#include "Rendering/Font.h"
#include "Rendering/Texture.h"

namespace Sourcehold {
namespace GUI {
/**
 * This handles the credits sequences,
 * the one in the main menu and the endgame credits.
 */
class Credits : protected Events::EventConsumer<Events::Mouse> {
  bool playing;
  Layout layout;

 public:
  Credits();
  Credits(const Credits &) = delete;
  ~Credits();

  bool Play(bool endgame, bool fadein, bool loop);

 protected:
  void onEventReceive(Events::Mouse &event) override;
};
}  // namespace GUI
}  // namespace Sourcehold
