

#include <Hexagon/ComponentBitmapRenderCreator.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


ComponentBitmapRenderCreator::ComponentBitmapRenderCreator(Blast::Project::Component* component)
   : component(component)
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
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "ComponentBitmapRenderCreator" << "::" << "create_bitmap_render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return nullptr;
}

std::string ComponentBitmapRenderCreator::render()
{
   return "Hello World!";
}
} // namespace Hexagon


