

#include <Hexagon/Forms/Fun.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Forms
{


Fun::Fun()
{
}


Fun::~Fun()
{
}


std::string Fun::run()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "run" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "run" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "run" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
      throw std::runtime_error(error_message.str());
   }
return "Hello World!";
}
} // namespace Forms
} // namespace Hexagon


