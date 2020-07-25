#pragma once

#include <cinttypes>
#include <memory>
#include <string>
#include <vector>

#include "Assets.h"
#include "Audio/Song.h"
#include "Events/Event.h"
#include "Events/Mouse.h"
#include "Parsers/TgxFile.h"

/* Narration screens shown before campaign missions */
namespace Sourcehold {
namespace GUI {
enum class NarrBackground { GOODGUYS, BADGUYS };

#define NUM_ANIM_FRAMES 13
class NarrScreen : protected Events::EventConsumer<Events::Mouse> {
  std::vector<std::wstring> lines;
  Audio::Song song;
  bool skipped;
  uint8_t mission;
  std::shared_ptr<TgxFile> tgx_bg1, tgx_bg2, tgx_candle[NUM_ANIM_FRAMES],
      tgx_flame[2][NUM_ANIM_FRAMES];

 public:
  /* Create sequence based on mission index */
  NarrScreen(uint8_t mission);
  ~NarrScreen();

  bool Begin();

 protected:
  void onEventReceive(Events::Mouse &mouse) override;

  bool BeginAct(Assets::TextSection text);
  bool BeginNarration();
  bool BeginStoryScreen(NarrBackground bg);
  bool BeginNpcIntro(Assets::NPC npc);

  void RenderFlameAnim(int px, int py, int index, Uint8 alpha);
  void NarrationText(Assets::TextSection text);
};
}  // namespace GUI
}  // namespace Sourcehold
