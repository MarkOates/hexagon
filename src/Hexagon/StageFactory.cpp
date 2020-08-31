

#include <Hexagon/StageFactory.hpp>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


StageFactory::StageFactory()
{
}


StageFactory::~StageFactory()
{
}


StageInterface* StageFactory::create()
{
return nullptr;

}

ALLEGRO_DISPLAY* StageFactory::get_current_display()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "get_current_display" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "StageFactory" << "::" << "get_current_display" << ": error: " << "guard \"al_get_current_display()\" not met";
      throw std::runtime_error(error_message.str());
   }
return al_get_current_display();

}

placement3d StageFactory::build_component_navigator_initial_place()
{
ALLEGRO_DISPLAY *display = get_current_display();
placement3d result;
result.position = vec3d(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
result.size = vec3d(800, 700, 0);
result.align = vec3d(0.5, 0.5, 0.5);
result.scale = vec3d(1.0, 1.0, 1.0);
result.rotation = vec3d(0.0, 0.0, 0.0);
return result;

}
} // namespace Hexagon


