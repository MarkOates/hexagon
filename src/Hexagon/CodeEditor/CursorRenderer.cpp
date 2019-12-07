

#include <Hexagon/CodeEditor/CursorRenderer.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <allegro_flare/color.h>


namespace Hexagon
{
namespace CodeEditor
{


CursorRenderer::CursorRenderer(float x, float y, float width, float height, ::CodeEditor::Stage::mode_t mode, bool focus)
   : x(x)
   , y(y)
   , width(width)
   , height(height)
   , mode(mode)
   , focus(focus)
{
}


CursorRenderer::~CursorRenderer()
{
}


void CursorRenderer::render()
{
float cursor_x = x;
float _cursor_x = x;
float _cursor_y = y;
float _cell_width = width;
float cell_height = height;
ALLEGRO_COLOR cursor_color = al_color_name("chartreuse");
float cursor_outset = 2.0;
float cursor_thickness = 3.0;

float x = 0;
float y = 0;
float x2 = 1;
float y2 = 1;

ALLEGRO_COLOR halo_color = cursor_color;

switch(mode)
{
case ::CodeEditor::Stage::EDIT:
  {
     x = cursor_x*_cell_width - cursor_outset;
     y = _cursor_y*cell_height - cursor_outset;
     x2 = cursor_x*_cell_width + _cell_width + cursor_outset;
     y2 = _cursor_y*cell_height + cell_height;
     al_draw_rounded_rectangle(x, y, x2, y2, 2.0, 2.0, cursor_color, cursor_thickness);
  }
  break;
case ::CodeEditor::Stage::INSERT:
  {
     x = cursor_x*_cell_width;
     y = _cursor_y*cell_height;
     x2 = cursor_x*_cell_width;
     y2 = _cursor_y*cell_height + cell_height;
     al_draw_line(x, y, x2, y2, cursor_color, cursor_thickness);
  }
  break;
default:
  throw std::runtime_error("Hexagon/CodeEditor/CursorRenderer: unsupported Stage::mode_t");
  break;
}

if (focus)
{
   int max_outset = 23;
   for (int outset=1; outset<max_outset; outset++)
   {
     float color_opacity = (1.0 - (float)outset / max_outset) * 0.25;
     ALLEGRO_COLOR col = color::color(halo_color, color_opacity);
     al_draw_rounded_rectangle(
       x - outset,
       y - outset,
       x2 + outset,
       y2 + outset,
       2.0, 2.0, col, cursor_thickness);
   }
}

}
} // namespace CodeEditor
} // namespace Hexagon


