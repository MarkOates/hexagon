

#include <Hexagon/Elements/FlashingGrid.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


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
   , counter(0)
{
}


FlashingGrid::~FlashingGrid()
{
}


void FlashingGrid::set_counter(int counter)
{
   this->counter = counter;
}


void FlashingGrid::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[FlashingGrid::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FlashingGrid::render: error: guard \"al_is_system_installed()\" not met");
   }
   // note: missing guard for al_is_primitives_addon_initialized();
   ALLEGRO_COLOR box_color;

   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         box_color = ((x+y+counter)%5 == 0) ? al_color_name("white") : al_color_name("gray");
         float xx = x * (box_size + 14);
         float yy = y * (box_size + 14);
         al_draw_filled_rectangle(xx, yy, xx+box_size, yy+box_size, box_color);
      }
   }
   return;
}


} // namespace Elements
} // namespace Hexagon


