

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
   , character_uv_mapping({})
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


std::map<char, std::tuple<float, float, float, float>> FontCharacterMapGrid::get_character_uv_mapping()
{
   return character_uv_mapping;
}


ALLEGRO_BITMAP* FontCharacterMapGrid::create()
{
if (!(font))
   {
      std::stringstream error_message;
      error_message << "FontCharacterMapGrid" << "::" << "create" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
character_uv_mapping.clear();

grid_width = al_get_text_width(font, "W"); // 'W' character as an estimate for reasonable large width
grid_height = al_get_font_line_height(font);
int num_rows = 16;
int num_columns = 16;
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
      char char_number = x + y * num_rows;
      text_to_draw[0] = x + y * num_rows;
      al_draw_text(font, text_color, x * grid_width, y * grid_height, ALLEGRO_ALIGN_LEFT, text_to_draw_cstr);
      float u1 = x * grid_width;
      float v1 = y * grid_height;
      float u2 = u1 + grid_width;
      float v2 = v2 + grid_height;
      character_uv_mapping[char_number] = {u1, v1, u2, v2};
   }
}
al_restore_state(&previous_state);
return result;

}
} // namespace Elements
} // namespace Hexagon


