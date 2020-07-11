

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::Elements::TextMesh* text_mesh)
   : text_mesh(text_mesh)
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
text_mesh->render();
return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


