

#include <Hexagon/Elements/FlashingGrid.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


FlashingGrid::FlashingGrid()
{
}


FlashingGrid::~FlashingGrid()
{
}


void FlashingGrid::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "FlashingGrid" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
// note: missing guard for al_is_primitives_addon_initialized();
al_draw_filled_rectangle(0, 0, 10, 10, al_color_name("white"));
return;

}
} // namespace Elements
} // namespace Hexagon


