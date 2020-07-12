

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::Elements::TextMesh* text_mesh, Hexagon::AdvancedCodeEditor::Cursor* cursor)
   : text_mesh(text_mesh)
   , cursor(cursor)
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
text_mesh->render();
al_draw_rectangle(
   cursor->get_x(),
   cursor->get_y(),
   cursor->get_x()+cursor->get_width(),
   cursor->get_y()+cursor->get_height(),
   ALLEGRO_COLOR{0.0f, 1.0f, 1.0f, 1.0f},
   2.0f
   );
return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


