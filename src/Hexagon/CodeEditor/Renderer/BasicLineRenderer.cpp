

#include <Hexagon/CodeEditor/Renderer/BasicLineRenderer.hpp>
#include <sstream>
#include <allegro5/allegro.h>
#include <allegro5/allegro.h>


namespace Hexagon
{
namespace CodeEditor
{
namespace Renderer
{


BasicLineRenderer::BasicLineRenderer()
   : font(nullptr)
   , font_color(nullptr)
   , x(0.0f)
   , y(0.0f)
   , truncated_line("")
{
}


BasicLineRenderer::~BasicLineRenderer()
{
}


std::string BasicLineRenderer::run()
{
return "Hello World!";
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


