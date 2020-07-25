#pragma once

#include <memory>

#include "Events/Event.h"
#include "Events/Keyboard.h"
#include "Events/Mouse.h"
#include "Events/Touch.h"
#include "GUI/Ingame.h"
#include "GUI/UIState.h"
#include "GameManager.h"
#include "GameMap.h"
#include "Parsers/Gm1File.h"
#include "Rendering/Camera.h"
#include "Rendering/Texture.h"

namespace Sourcehold {
namespace Parsers {
class TgxFile;
class Gm1File;
}  // namespace Parsers
namespace Game {
struct Scroll {
  bool shouldScroll = false;
  bool setByKeyboard = false;
  bool setByMouse = false;

  explicit operator bool() {
    return shouldScroll;
  }
};

struct ScrollInformation {
  Scroll up;
  Scroll down;
  Scroll right;
  Scroll left;
};

// Just testing. Nothing to see here, move along! //
class Unit {
 public:
  Unit(int x, int y, const char* f) : x(x), y(y) {
    file = GetGm1(std::string("gm/") + f + std::string(".gm1"));
  }

  virtual void Update(double dt){};

  void Render() {
    GUI::Camera& cam = GUI::Camera::instance();

    int px = x * 30 - cam.positionX;
    int py = y * 15 - cam.positionY;

    SDL_Rect r = file->GetTextureAtlas()->Get(index);
    Rendering::Render(*file->GetTextureAtlas(), px, py, &r);
  }

  int x, y;

 protected:
  int index = 0;
  std::shared_ptr<Parsers::Gm1File> file;
};

class Lord : Unit {
 public:
  Lord(int x, int y) : Unit(x, y, "body_lord") {
  }
};

class Oak : Unit {
 public:
  Oak(int x, int y) : Unit(x, y, "tree_oak") {
  }

  void Update(double dt) {
    index = (24 - abs(int(GetTime() * 15.0f) % (2 * 24) - 24));
  }
};

/**
 * Handles everything related to the game world, including
 * loading, rendering and moving the camera
 */
class Building;
class Entity;
class World : public GameMap,
              private Events::EventConsumer<Events::Keyboard>,
              private Events::EventConsumer<Events::Mouse>,
              private Events::EventConsumer<Events::Touch> {
  ScrollInformation scroll;
  GUI::IngameGUI gui;
  std::vector<Unit*> units;

 public:
  World();
  World(const World&) = delete;
  ~World();

  GUI::UIState Play();

 protected:
  void UpdateCamera(double dt);

  template <class T>
  void Spawn(int x, int y) {
    units.push_back((Unit*)new T(x, y));
  }

 private:
  void onEventReceive(Events::Keyboard& keyEvent) override;
  void onEventReceive(Events::Mouse& mouseEvent) override;
  void onEventReceive(Events::Touch& touchEvent) override;
};
}  // namespace Game
}  // namespace Sourcehold
