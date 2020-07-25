#pragma once

#include <cinttypes>
#include <memory>
#include <string>
#include <vector>

#include "GUI/NarrScreen.h"
#include "Parsers/HlpFile.h"
#include "Parsers/TgxFile.h"
#include "Rendering/Font.h"
#include "Rendering/Shapes.h"

namespace Sourcehold {
namespace GUI {

enum class PicPosition : uint8_t { LEFT, RIGHT, CENTRE };

struct LayoutElement {
  enum Type { LINE, PIC, PARAGRAPH, LINEBREAK } type;
  PicPosition pos;
  Rendering::Font font;
  std::wstring text;
  std::shared_ptr<TgxFile> pic;
  int x, y;
};

/**
 * Handles GUI layouts containing text and
 * images, which can be created manually
 * or by using the stronghold_help.hlp file.
 */
class Layout {
 public:
  Layout();
  Layout(Parsers::HlpSection *hlp,
         Rendering::Rect<double> bounds = {0.0, 0.0, 1.0, 1.0});
  ~Layout();

  void CreateFromHlp(Parsers::HlpSection *hlp);
  void Destroy();
  void Render(double x, double y);
  void Render(int x, int y);

  /* Modification calls */
  void SetFont(Rendering::Font index);
  void AddText(const std::wstring &str);
  void AddPic(std::shared_ptr<TgxFile> pic, PicPosition pos);
  void NewParagraph();

  inline void SetBounds(Rendering::Rect<double> bounds) {
    this->bounds = bounds;
  }

 protected:
  Rendering::Rect<double> bounds;
  std::vector<LayoutElement> elems;
  Rendering::Font currentFont = Rendering::FONT_SMALL;
  uint32_t width = 0, height = 0;
  std::vector<std::shared_ptr<TgxFile>> pics;
};
}  // namespace GUI
}  // namespace Sourcehold
