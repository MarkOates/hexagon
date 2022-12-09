

#include <Hexagon/Elements/CheckTextureGenerator.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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


ALLEGRO_BITMAP* CheckTextureGenerator::generate_grid_check()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[CheckTextureGenerator::generate_grid_check]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CheckTextureGenerator::generate_grid_check: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[CheckTextureGenerator::generate_grid_check]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("CheckTextureGenerator::generate_grid_check: error: guard \"display\" not met");
   }
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


