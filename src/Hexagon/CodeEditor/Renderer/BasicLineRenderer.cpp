

#include <Hexagon/CodeEditor/Renderer/BasicLineRenderer.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <sstream>


namespace Hexagon
{
namespace CodeEditor
{
namespace Renderer
{


BasicLineRenderer::BasicLineRenderer(ALLEGRO_FONT* font, ALLEGRO_COLOR* font_color, float x, float y, std::string truncated_line)
   : font(font)
   , font_color(font_color)
   , x(x)
   , y(y)
   , truncated_line(truncated_line)
{
}


BasicLineRenderer::~BasicLineRenderer()
{
}


void BasicLineRenderer::render()
{
   if (!font)
   {
      std::stringstream error_message;
      error_message << "[Hexagon/Powerbar/Renderer/BasicLineRenderer error:] cannot \""
                    << __FUNCTION__ << "\" with a nullptr font";
      throw std::runtime_error(error_message.str());
   }
   if (!font_color)
   {
      std::stringstream error_message;
      error_message << "[Hexagon/Powerbar/Renderer/BasicLineRenderer error:] cannot \""
                    << __FUNCTION__ << "\" with a nullptr font";
      throw std::runtime_error(error_message.str());
   }

   al_draw_text(font,
                *font_color,
                x,
                y, //(line_number-first_line_number)*cell_height,
                ALLEGRO_ALIGN_LEFT,
                truncated_line.c_str());
}


} // namespace Renderer
} // namespace CodeEditor
} // namespace Hexagon


