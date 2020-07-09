

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


FlashingGrid::FlashingGrid(float width, float height, int num_columns, int num_rows, int box_size)
   : width(width)
   , height(height)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , box_size(box_size)
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
for (int y=0; y<num_rows; y++)
{
   for (int x=0; x<num_columns; x++)
   {
      float xx = x * (box_size + 14);
      float yy = y * (box_size + 14);
      al_draw_filled_rectangle(xx, yy, xx+box_size, yy+box_size, al_color_name("white"));
   }
}
return;

}
} // namespace Elements
} // namespace Hexagon


