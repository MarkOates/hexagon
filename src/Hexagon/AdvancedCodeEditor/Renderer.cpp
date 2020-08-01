

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::Elements::TextMesh* text_mesh, Hexagon::AdvancedCodeEditor::Cursor* cursor, float width, float height, bool cursor_is_bar)
   : text_mesh(text_mesh)
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
if (!(cursor))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"cursor\" not met";
      throw std::runtime_error(error_message.str());
   }
// draw the window
Hexagon::AdvancedCodeEditor::WindowRenderer(
   width,
   height
).render();

// draw the mesh
text_mesh->render();

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


