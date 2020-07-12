

#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>
#include <Hexagon/Elements/Window.hpp>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


WindowRenderer::WindowRenderer(float width, float height)
   : width(width)
   , height(height)
{
}


WindowRenderer::~WindowRenderer()
{
}


void WindowRenderer::render()
{
Hexagon::Elements::Window window(width, height);

window.set_box_fill_color(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});
window.set_box_opacity(0.1);

window.draw();
return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


