

#include <Hexagon/CodeEditor/CursorRenderer.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


namespace Hexagon
{
namespace CodeEditor
{


CursorRenderer::CursorRenderer(float x, float y, float width, float height)
   : x(x)
   , y(y)
   , width(width)
   , height(height)
{
}


CursorRenderer::~CursorRenderer()
{
}


void CursorRenderer::render()
{
ALLEGRO_COLOR cursor_color = al_color_name("yellow");
float cursor_thickness = 1.0;
al_draw_rectangle(x, y, width, height, cursor_color, cursor_thickness);

}
} // namespace CodeEditor
} // namespace Hexagon


