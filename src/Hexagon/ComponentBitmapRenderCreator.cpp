

#include <Hexagon/ComponentBitmapRenderCreator.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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
      error_message << "[Hexagon::ComponentBitmapRenderCreator::create_bitmap_render]: error: guard \"component\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentBitmapRenderCreator::create_bitmap_render]: error: guard \"component\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::ComponentBitmapRenderCreator::create_bitmap_render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::ComponentBitmapRenderCreator::create_bitmap_render]: error: guard \"al_is_system_installed()\" not met");
   }
   return nullptr;
}

std::string ComponentBitmapRenderCreator::render()
{
   return "Hello World!";
}


} // namespace Hexagon


