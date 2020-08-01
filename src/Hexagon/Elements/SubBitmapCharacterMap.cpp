

#include <Hexagon/Elements/SubBitmapCharacterMap.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


SubBitmapCharacterMap::SubBitmapCharacterMap(ALLEGRO_FONT* font)
   : font(font)
   , grid_width(0)
   , grid_height(0)
   , cell_sub_bitmaps({})
{
}


SubBitmapCharacterMap::~SubBitmapCharacterMap()
{
}


void SubBitmapCharacterMap::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


int SubBitmapCharacterMap::get_grid_width()
{
   return grid_width;
}


int SubBitmapCharacterMap::get_grid_height()
{
   return grid_height;
}


std::map<char, ALLEGRO_BITMAP*> SubBitmapCharacterMap::get_cell_sub_bitmaps()
{
   return cell_sub_bitmaps;
}


ALLEGRO_BITMAP* SubBitmapCharacterMap::create()
{
if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "SubBitmapCharacterMap" << "::" << "create" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(font))
   {
      std::stringstream error_message;
      error_message << "SubBitmapCharacterMap" << "::" << "create" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
for (auto &cell_sub_bitmap : cell_sub_bitmaps) al_destroy_bitmap(cell_sub_bitmap.second);
cell_sub_bitmaps.clear();

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
      int xx = x * grid_width;
      int yy = y * grid_height;
      int ww = grid_width;
      int hh = grid_height;

      ALLEGRO_BITMAP *cell_sub_bitmap = al_create_sub_bitmap(result, xx, yy, ww, hh);
      cell_sub_bitmaps[(char)(x + y*num_columns)] = cell_sub_bitmap;
   }
}
al_restore_state(&previous_state);
return result;

}
} // namespace Elements
} // namespace Hexagon


