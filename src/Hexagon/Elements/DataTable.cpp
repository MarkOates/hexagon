

#include <Hexagon/Elements/DataTable.hpp>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include <string>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


DataTable::DataTable(ALLEGRO_FONT* font, float column_width, float row_height, std::vector<std::vector<std::string>> data2d)
   : font(font)
   , column_width(column_width)
   , row_height(row_height)
   , data2d(data2d)
{
}


DataTable::~DataTable()
{
}


void DataTable::render()
{
if (!(font))
   {
      std::stringstream error_message;
      error_message << "DataTable" << "::" << "render" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "DataTable" << "::" << "render" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5};

std::vector<std::vector<std::string>> table = {
   { "SEARCHES", "22", "DOPPER", "Active", "Running"},
   { "SAVES",    "11", "DOPPER"},
   { "SCORE",    "97", "DOPPER"},
};

int row_num = 0;
int column_num = 0;
float first_row_x = 22;
//float column_width = 95;
float first_row_y = 20;
//int row_height = al_get_font_line_height(font) * 1.2;

for (auto &row : table)
{
   int column_num = 0;
   for (auto &cell : row)
   {
      float x = first_row_x + column_width * column_num;
      float y = first_row_y + row_height * row_num;
      std::string text_to_draw = cell;
      ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
      ALLEGRO_FONT *font = this->font;
      al_draw_text(font, text_color, x, y, ALLEGRO_ALIGN_LEFT, text_to_draw.c_str());
      column_num++;
   }
   row_num++;
}

return;

}
} // namespace Elements
} // namespace Hexagon


