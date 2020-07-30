

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <Hexagon/AdvancedCodeEditor/WindowRenderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::Elements::TextMesh* text_mesh, Hexagon::AdvancedCodeEditor::Cursor* cursor, float width, float height)
   : text_mesh(text_mesh)
   , cursor(cursor)
   , width(width)
   , height(height)
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

// draw the cursor
al_draw_rectangle(
   cursor_x,
   cursor_y,
   cursor_x+cursor->get_width(),
   cursor_y+cursor->get_height(),
   ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f},
   2.0f
   );

return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


