

#include <Hexagon/AdvancedCodeEditor/Renderer.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace AdvancedCodeEditor
{


Renderer::Renderer(Hexagon::AdvancedCodeEditor::Stage* stage)
   : stage(stage)
{
}


Renderer::~Renderer()
{
}


void Renderer::render()
{
if (!(stage))
   {
      std::stringstream error_message;
      error_message << "Renderer" << "::" << "render" << ": error: " << "guard \"stage\" not met";
      throw std::runtime_error(error_message.str());
   }
//stage->get_mesh()
return;

}
} // namespace AdvancedCodeEditor
} // namespace Hexagon


