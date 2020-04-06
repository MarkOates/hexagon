

#include <Hexagon/Elements/CheckTextures.hpp>
#include <sstream>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


CheckTextures::CheckTextures(ALLEGRO_DISPLAY* display)
   : display(display)
{
}


CheckTextures::~CheckTextures()
{
}


void CheckTextures::validate_al_init(std::string function_name)
{
if (!al_is_system_installed())
{
   std::stringstream error_message;
   error_message << "[Hexagon/Elements/CheckTextures error:] cannot \"" << function_name << "\" before al_init()";
   throw std::runtime_error(error_message.str());
}
return;

}

void CheckTextures::validate_display(std::string function_name)
{
if (!display)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Elements/CheckTextures error:] cannot \""
                 << function_name
                 << "\" with a nullptr display";
   throw std::runtime_error(error_message.str());
}
return;

}

ALLEGRO_BITMAP* CheckTextures::generate_grid_check()
{
validate_al_init(__FUNCTION__);
validate_display(__FUNCTION__);

ALLEGRO_BITMAP *result = al_create_bitmap(400, 300);

return result;

}
} // namespace Elements
} // namespace Hexagon


