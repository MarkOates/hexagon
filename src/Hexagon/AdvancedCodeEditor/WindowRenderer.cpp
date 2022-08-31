

#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>

#include <Hexagon/ElementFX/WindowSpawnMotionFX.hpp>
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
   window.set_cell_padding(-15);

   window.set_outer_line_color(ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});
   window.set_outer_line_thickness(1.0f);
   window.set_outer_line_opacity(0.2f);

   Hexagon::ElementFX::WindowSpawnMotionFX window_spawn_motion_fx(window);
   window = window_spawn_motion_fx.construct_modified_window();

   window.draw();
   return;
}


} // namespace AdvancedCodeEditor
} // namespace Hexagon


