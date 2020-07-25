#pragma once

#include <memory>
#include <vector>

#include "GUI/Widgets/Widget.h"
#include "Rendering/Shapes.h"

namespace Sourcehold {
namespace GUI {
enum class WidgetLayout { VERTICAL, HORIZONTAL };

class Container : public Widget {
  std::vector<std::shared_ptr<Widget>> widgets;
  WidgetLayout layout;
  Rendering::Rect<int> constraints;

 public:
  Container(WidgetLayout l);
  ~Container() {
  }

  void Update(Rendering::Rect<int> constraints) override;

  /** Add a widget to the container. */
  template <typename T, typename... Args>
  std::shared_ptr<T> Add(Args... args) {
    static_assert(std::is_base_of<Widget, T>::value,
                  "Template parameter must be a widget!");
    auto widget = std::make_shared<T>(args...);
    widgets.push_back(widget);
    return widget;
  }
};
}  // namespace GUI
}  // namespace Sourcehold
