

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <iostream>
#include <allegro5/allegro.h>
#include <AllegroFlare/Timer.hpp>
#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::Elements::TextMesh* text_mesh, ALLEGRO_BITMAP* surface_render, Hexagon::Elements::FontedTextGrid* fonted_text_grid, Hexagon::AdvancedCodeEditor::Cursor* cursor, float width, float height, bool cursor_is_bar)
   : text_mesh(text_mesh)
   , surface_render(surface_render)
   , fonted_text_grid(fonted_text_grid)
   , cursor(cursor)
   , width(width)
   , height(height)
   , cursor_is_bar(cursor_is_bar)
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"text_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(fonted_text_grid))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"fonted_text_grid\" not met";
      throw std::runtime_error(error_message.str());
   }
AllegroFlare::Timer timer;

timer.reset(); timer.start();
// draw the window
Hexagon::AdvancedCodeEditor::WindowRenderer(
   width,
   height
).render();
timer.pause(); std::cout << " window render: " << timer.get_elapsed_time_microseconds() << std::endl;

// draw the surface render
timer.reset(); timer.start();
if (surface_render) al_draw_bitmap(surface_render, 0, 0, 0);
timer.pause(); std::cout << " surface_render render time: " << timer.get_elapsed_time_microseconds() << std::endl;

// draw the cursor
render_cursor();

return;

}

void Renderer::render_cursor()
{
if (!(text_mesh))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_cursor" << ": error: " << "guard \"text_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(cursor))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_cursor" << ": error: " << "guard \"cursor\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render_cursor" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
float cursor_x = cursor->get_x() * text_mesh->get_cell_width();
float cursor_y = cursor->get_y() * text_mesh->get_cell_height();
ALLEGRO_COLOR cursor_color = ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f};

if (cursor_is_bar)
{
   // draw the cursor
   al_draw_line(
      cursor_x,
      cursor_y,
      cursor_x,
      cursor_y+cursor->get_height(),
      cursor_color,
      2.0f
      );
}
else
{
   // draw the cursor
   al_draw_rectangle(
      cursor_x,
      cursor_y,
      cursor_x+cursor->get_width(),
      cursor_y+cursor->get_height(),
      cursor_color,
      2.0f
      );
}
return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


