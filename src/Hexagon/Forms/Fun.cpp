

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


Fun::Fun(placement3d place, ALLEGRO_COLOR backfill_color)
   : place(place)
   , backfill_color(backfill_color)
{
}


Fun::~Fun()
{
}


void Fun::set_place(placement3d place)
{
   this->place = place;
}


void Fun::set_backfill_color(ALLEGRO_COLOR backfill_color)
{
   this->backfill_color = backfill_color;
}


placement3d Fun::get_place()
{
   return place;
}


ALLEGRO_COLOR Fun::get_backfill_color()
{
   return backfill_color;
}


void Fun::draw()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "draw" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "draw" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_get_target_bitmap()))
   {
      std::stringstream error_message;
      error_message << "Fun" << "::" << "draw" << ": error: " << "guard \"al_get_target_bitmap()\" not met";
      throw std::runtime_error(error_message.str());
   }
al_draw_filled_rectangle(0, 0, place.size.x, place.size.y, backfill_color);
return;

}
} // namespace Forms
} // namespace Hexagon


