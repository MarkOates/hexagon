

#include <Hexagon/Elements/DataTable.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


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
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "DataTable" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font))
   {
      std::stringstream error_message;
      error_message << "DataTable" << "::" << "render" << ": error: " << "guard \"font\" not met";
      throw std::runtime_error(error_message.str());
   }
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.5, 0.5, 0.5, 0.5};

   int row_num = 0;
   int column_num = 0;

   for (auto &row : data2d)
   {
      int column_num = 0;
      for (auto &cell : row)
      {
         float x = column_width * column_num;
         float y = row_height * row_num;
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


