

#include <Hexagon/System/Renderer.hpp>



namespace Hexagon
{
namespace System
{


Renderer::Renderer()
   : system(nullptr)
{
}


Renderer::~Renderer()
{
}


bool Renderer::render()
{
if (!system)
{
   std::stringstream error_message;
   error_message << "[System::Renderer error:] cannot render() with a nullptr system";
   throw std::runtime_error(error_message.str());
}
return true;

}
} // namespace System
} // namespace Hexagon


