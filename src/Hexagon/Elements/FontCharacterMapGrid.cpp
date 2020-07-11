

#include <Hexagon/Elements/FontCharacterMapGrid.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


FontCharacterMapGrid::FontCharacterMapGrid(ALLEGRO_FONT* font)
   : font(font)
   , grid_width(0)
   , grid_height(0)
{
}


FontCharacterMapGrid::~FontCharacterMapGrid()
{
}


int FontCharacterMapGrid::get_grid_width()
{
   return grid_width;
}


int FontCharacterMapGrid::get_grid_height()
{
   return grid_height;
}


ALLEGRO_BITMAP* FontCharacterMapGrid::create()
{
if (!(font))
   {
      std::stringstream error_message;
      error_message << "FontCharacterMapGrid" << "::" << "create" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
grid_width = al_get_text_width(font, "W"); // 'W' character as an estimate for reasonable large width
grid_height = al_get_font_line_height(font);
int num_rows = 10;
int num_columns = 20;
ALLEGRO_STATE previous_state;
al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);

ALLEGRO_BITMAP *result = al_create_bitmap(grid_width * num_columns, grid_height * num_rows);
al_set_target_bitmap(result);
al_clear_to_color(ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});


ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f};
std::string text_to_draw = " ";
const char* text_to_draw_cstr = text_to_draw.c_str();
for (int y=0; y<=num_rows; y++)
{
   for (int x=0; x<=num_columns; x++)
   {
      text_to_draw[0] = x + y * num_rows;
      al_draw_text(font, text_color, x * grid_width, y * grid_height, ALLEGRO_ALIGN_LEFT, text_to_draw_cstr);
   }
}
al_restore_state(&previous_state);
return result;

}
} // namespace Elements
} // namespace Hexagon


