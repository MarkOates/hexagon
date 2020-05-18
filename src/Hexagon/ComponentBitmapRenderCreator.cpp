

#include <Hexagon/ComponentBitmapRenderCreator.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


ComponentBitmapRenderCreator::ComponentBitmapRenderCreator()
   : component(nullptr)
{
}


ComponentBitmapRenderCreator::~ComponentBitmapRenderCreator()
{
}


ALLEGRO_BITMAP* ComponentBitmapRenderCreator::create_bitmap_render()
{
if (!(component))
   {
      std::stringstream error_message;
      error_message << "ComponentBitmapRenderCreator" << "::" << "create_bitmap_render" << ": error: " << "guard \"component\" not met";
      throw std::runtime_error(error_message.str());
   }
return nullptr;

}

std::string ComponentBitmapRenderCreator::render()
{
if (!(component))
   {
      std::stringstream error_message;
      error_message << "ComponentBitmapRenderCreator" << "::" << "render" << ": error: " << "guard \"component\" not met";
      throw std::runtime_error(error_message.str());
   }
return "Hello World!";
}
} // namespace Hexagon


