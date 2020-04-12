

#include <Hexagon/CodeEditor/Renderer/AdvancedLineRenderer.hpp>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro.h>


namespace Hexagon
{
namespace CodeEditor
{
namespace Renderer
{


AdvancedLineRenderer::AdvancedLineRenderer(ALLEGRO_FONT* font, ALLEGRO_COLOR* font_color, float x, float y, std::string line)
   : font(font)
   , font_color(font_color)
   , x(x)
   , y(y)
   , line(line)
{
}


AdvancedLineRenderer::~AdvancedLineRenderer()
{
}


void AdvancedLineRenderer::render()
{
if (!font)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Powerbar/Renderer/AdvancedLineRenderer error:] cannot \""
                 << __FUNCTION__ << "\" with a nullptr font";
   throw std::runtime_error(error_message.str());
}
if (!font_color)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Powerbar/Renderer/AdvancedLineRenderer error:] cannot \""
                 << __FUNCTION__ << "\" with a nullptr font";
   throw std::runtime_error(error_message.str());
}

std::size_t comment_starts_at = line.find("//");
//std::string uncommented
//float character_width = al_get_text_width(

al_draw_text(font,
             *font_color,
             x,
             y, //(line_number-first_line_number)*cell_height,
             ALLEGRO_ALIGN_LEFT,
             line.c_str());

}
} // namespace Renderer
} // namespace CodeEditor
} // namespace Hexagon


