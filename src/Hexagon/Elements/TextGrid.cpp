

#include <Hexagon/Elements/TextGrid.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_color.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


TextGrid::TextGrid(ALLEGRO_FONT* font, int num_columns, int num_rows, float cell_width, float cell_height)
   : font(font)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , cell_width(cell_width)
   , cell_height(cell_height)
{
}


TextGrid::~TextGrid()
{
}


void TextGrid::set_cell_color(int x, int y, ALLEGRO_COLOR color)
{
return;

}

void TextGrid::render()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "TextGrid" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
// note: missing guard for al_is_primitives_addon_initialized();
ALLEGRO_COLOR box_color;

for (int y=0; y<num_rows; y++)
{
   for (int x=0; x<num_columns; x++)
   {
      box_color = ((x+y)%5 == 0) ? al_color_name("white") : al_color_name("gray");
      float xx = x * (cell_width);
      float yy = y * (cell_height);
      al_draw_filled_rectangle(xx, yy, xx+cell_width, yy+cell_height, box_color);
   }
}
return;

}
} // namespace Elements
} // namespace Hexagon


