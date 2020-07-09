

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


TextGrid::TextGrid(ALLEGRO_FONT* font, int num_columns, int num_rows, float cell_width, float cell_height, std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid)
   : font(font)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , grid(grid)
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
int y=0;
for (auto &grid_line : grid)
{
   int x=0;
   for (auto &grid_box : grid_line)
   {
      //std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR> &box = grid_box;
      char character = std::get<0>(grid_box);
      ALLEGRO_COLOR background_color = std::get<1>(grid_box);
      ALLEGRO_COLOR foreground_color = std::get<2>(grid_box);
      float xx = x * cell_width;
      float yy = y * cell_height;

      // draw background
      al_draw_filled_rectangle(xx, yy, xx+cell_width, yy+cell_height, background_color);

      // draw foreground
      al_draw_text(font, foreground_color, xx, yy, 0, std::to_string((char)character).c_str());

      x++;
   }
   y++;
}
return;

}
} // namespace Elements
} // namespace Hexagon


