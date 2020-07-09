

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


TextGrid::TextGrid(ALLEGRO_FONT* font, float cell_width, float cell_height, float cell_spacing_x, float cell_spacing_y, std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> grid)
   : font(font)
   , cell_width(cell_width)
   , cell_height(cell_height)
   , cell_spacing_x(cell_spacing_x)
   , cell_spacing_y(cell_spacing_y)
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
std::string str_to_render = "\0";
for (auto &grid_line : grid)
{
   int x=0;
   for (auto &grid_box : grid_line)
   {
      //std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR> &box = grid_box;
      str_to_render[0] = std::get<0>(grid_box);
      ALLEGRO_COLOR foreground_color = std::get<1>(grid_box);
      ALLEGRO_COLOR background_color = std::get<2>(grid_box);
      float xx = x * (cell_width + cell_spacing_x);
      float yy = y * (cell_height + cell_spacing_y);

      // draw background
      al_draw_filled_rectangle(xx, yy, xx+cell_width, yy+cell_height, background_color);

      // draw foreground
      if (str_to_render[0] != ' ') al_draw_text(font, foreground_color, xx, yy, 0, str_to_render.c_str());

      x++;
   }
   y++;
}
return;

}
} // namespace Elements
} // namespace Hexagon


