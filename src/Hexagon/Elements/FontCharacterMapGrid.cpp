

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
//throw std::runtime_error("aaa"); //int character_width = al_get_text_width(font, "W"); // 'W' character as an estimate for reasonable large width //int character_height = al_get_font_line_height(font);
ALLEGRO_BITMAP *result = al_create_bitmap(800, 600); //for (int y=0; y<=10; y++) //{ //for (int x=0; x<=10; x++) //{ //al_draw_text(font, //} //} return result;
}
} // namespace Elements
} // namespace Hexagon


