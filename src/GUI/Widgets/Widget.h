#pragma once

#include "Rendering/Shapes.h"

namespace Sourcehold {
namespace GUI {
struct Widget {
  Widget(const Widget&) = delete;
  Widget& operator=(const Widget&) = delete;
  Widget() = default;

  virtual ~Widget(){};
  virtual void Update(Rendering::Rect<int> constraints) = 0;
};
}  // namespace GUI
}  // namespace Sourcehold
