

#include <Hexagon/CodeEditor/CursorRenderer.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>


namespace Hexagon
{
namespace CodeEditor
{


CursorRenderer::CursorRenderer(float x, float y, float width, float height, ::CodeEditor::Stage::mode_t mode)
   : x(x)
   , y(y)
   , width(width)
   , height(height)
   , mode(mode)
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

switch(mode)
{
case ::CodeEditor::Stage::EDIT:
  {
     float x = cursor_x*_cell_width - cursor_outset;
     float y = _cursor_y*cell_height - cursor_outset;
     float x2 = cursor_x*_cell_width + _cell_width + cursor_outset;
     float y2 = _cursor_y*cell_height + cell_height;
     al_draw_rounded_rectangle(x, y, x2, y2, 2.0, 2.0, cursor_color, cursor_thickness);
     break;
  }
case ::CodeEditor::Stage::INSERT:
  {
     float x = cursor_x*_cell_width;
     float y = _cursor_y*cell_height;
     float x2 = cursor_x*_cell_width;
     float y2 = _cursor_y*cell_height + cell_height;
     al_draw_line(x, y, x2, y2, cursor_color, cursor_thickness);
     break;
  }
}

}
} // namespace CodeEditor
} // namespace Hexagon


