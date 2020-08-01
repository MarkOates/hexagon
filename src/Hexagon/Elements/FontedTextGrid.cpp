

#include <Hexagon/Elements/FontedTextGrid.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace Elements
{


FontedTextGrid::FontedTextGrid(ALLEGRO_FONT* font, int num_columns, int num_rows)
   : font(font)
   , num_columns(num_columns)
   , num_rows(num_rows)
   , sub_bitmap_character_map({})
   , bitmap_grid_render_surface(num_columns, num_rows)
   , initialized(false)
{
}


FontedTextGrid::~FontedTextGrid()
{
}


void FontedTextGrid::set_font(ALLEGRO_FONT* font)
{
   this->font = font;
}


bool FontedTextGrid::get_initialized()
{
   return initialized;
}


void FontedTextGrid::initialize()
{
if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "FontedTextGrid" << "::" << "initialize" << ": error: " << "guard \"(!get_initialized())\" not met";
      throw std::runtime_error(error_message.str());
   }
sub_bitmap_character_map.set_font(font);
sub_bitmap_character_map.initialize();

bitmap_grid_render_surface.set_cell_width(al_get_text_width(font, "W"));
bitmap_grid_render_surface.set_cell_height(al_get_font_line_height(font));
bitmap_grid_render_surface.initialize();

initialized = true;
return;

}

void FontedTextGrid::destroy()
{
if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "FontedTextGrid" << "::" << "destroy" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
sub_bitmap_character_map.destroy();
bitmap_grid_render_surface.destroy();
initialized = false;
return;

}

void FontedTextGrid::set_cell_to_character_and_color(char character, int x, int y, ALLEGRO_COLOR tint)
{
if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "FontedTextGrid" << "::" << "set_cell_to_character_and_color" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_BITMAP *bitmap_to_draw = sub_bitmap_character_map.find_sub_bitmap(character);
bitmap_grid_render_surface.draw_to_cell(bitmap_to_draw, tint, x, y);
return;

}

void FontedTextGrid::draw()
{
if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "FontedTextGrid" << "::" << "draw" << ": error: " << "guard \"get_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
ALLEGRO_BITMAP *surface = bitmap_grid_render_surface.get_surface();
if (surface) al_draw_bitmap(surface, 0, 0, 0);
return;

}
} // namespace Elements
} // namespace Hexagon


