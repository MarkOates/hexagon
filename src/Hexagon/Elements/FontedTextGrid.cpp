

#include <Hexagon/Elements/FontedTextGrid.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


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


int FontedTextGrid::get_num_columns() const
{
   return num_columns;
}


int FontedTextGrid::get_num_rows() const
{
   return num_rows;
}


bool FontedTextGrid::get_initialized() const
{
   return initialized;
}


void FontedTextGrid::initialize()
{
   if (!((!get_initialized())))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::FontedTextGrid::initialize]: error: guard \"(!get_initialized())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::FontedTextGrid::initialize]: error: guard \"(!get_initialized())\" not met");
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
      error_message << "[Hexagon::Elements::FontedTextGrid::destroy]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::FontedTextGrid::destroy]: error: guard \"get_initialized()\" not met");
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
      error_message << "[Hexagon::Elements::FontedTextGrid::set_cell_to_character_and_color]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::FontedTextGrid::set_cell_to_character_and_color]: error: guard \"get_initialized()\" not met");
   }
   ALLEGRO_BITMAP *bitmap_to_draw = sub_bitmap_character_map.find_sub_bitmap(character);
   bitmap_grid_render_surface.draw_to_cell(bitmap_to_draw, tint, x, y);
   return;
}

void FontedTextGrid::lock_for_update()
{
   bitmap_grid_render_surface.lock_for_render();
   return;
}

void FontedTextGrid::unlock_for_update()
{
   bitmap_grid_render_surface.unlock_for_render();
   return;
}

void FontedTextGrid::draw()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::FontedTextGrid::draw]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::FontedTextGrid::draw]: error: guard \"get_initialized()\" not met");
   }
   ALLEGRO_BITMAP *surface = bitmap_grid_render_surface.get_surface();
   if (surface) al_draw_bitmap(surface, 0, 0, 0);
   return;
}

ALLEGRO_BITMAP* FontedTextGrid::__cheat_really_badly_and_get_the_bitmap_grid_render_surface()
{
   if (!(get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Elements::FontedTextGrid::__cheat_really_badly_and_get_the_bitmap_grid_render_surface]: error: guard \"get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::Elements::FontedTextGrid::__cheat_really_badly_and_get_the_bitmap_grid_render_surface]: error: guard \"get_initialized()\" not met");
   }
   return bitmap_grid_render_surface.get_surface();
}


} // namespace Elements
} // namespace Hexagon


