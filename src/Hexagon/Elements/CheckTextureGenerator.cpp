

#include <Hexagon/Elements/CheckTextureGenerator.hpp>
#include <sstream>
#include <sstream>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>


namespace Hexagon
{
namespace Elements
{


CheckTextureGenerator::CheckTextureGenerator(ALLEGRO_DISPLAY* display)
   : display(display)
{
}


CheckTextureGenerator::~CheckTextureGenerator()
{
}


void CheckTextureGenerator::validate_al_init(std::string function_name)
{
if (!al_is_system_installed())
{
   std::stringstream error_message;
   error_message << "[Hexagon/Elements/CheckTextureGenerator error:] cannot \""
                 << function_name
                 << "\" before al_init()";
   throw std::runtime_error(error_message.str());
}
return;

}

void CheckTextureGenerator::validate_display(std::string function_name)
{
if (!display)
{
   std::stringstream error_message;
   error_message << "[Hexagon/Elements/CheckTextureGenerator error:] cannot \""
                 << function_name
                 << "\" with a nullptr display";
   throw std::runtime_error(error_message.str());
}
return;

}

ALLEGRO_BITMAP* CheckTextureGenerator::generate_grid_check()
{
validate_al_init(__FUNCTION__);
validate_display(__FUNCTION__);

float width = 400;
float height = 300;

ALLEGRO_BITMAP *result = al_create_bitmap(width, height);
ALLEGRO_STATE previous_bitmap_state;
al_store_state(&previous_bitmap_state, ALLEGRO_STATE_TARGET_BITMAP);
al_clear_to_color(al_map_rgba_f(0.0f, 0.0f, 0.0f, 0.0f));
al_draw_rectangle(0, 0, width, height, al_color_name("pink"), 2.0f);
al_restore_state(&previous_bitmap_state);

return result;

}
} // namespace Elements
} // namespace Hexagon


