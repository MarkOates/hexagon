#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace Elements
   {
      class ListMenu
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string title;
         std::vector<std::tuple<std::string, std::string>> list_items;
         ALLEGRO_COLOR color;
         int cursor;
         bool wrap_cursor_when_moving_cursor_outside_bounds;
         bool upcase;
         int width;

      public:
         ListMenu(AllegroFlare::FontBin* font_bin=nullptr, std::string title="+", std::vector<std::tuple<std::string, std::string>> list_items={}, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 0, 0, 1});
         ~ListMenu();

         void set_wrap_cursor_when_moving_cursor_outside_bounds(bool wrap_cursor_when_moving_cursor_outside_bounds);
         void set_upcase(bool upcase);
         void set_width(int width);
         bool get_wrap_cursor_when_moving_cursor_outside_bounds();
         bool get_upcase();
         int get_width();
         bool move_cursor_up();
         bool move_cursor_down();
         std::string get_current_list_item_identifier();
         void render();
         ALLEGRO_FONT* obtain_list_item_font();
         void draw_cursor_pointer_arrow(float cpx=1000, float cpy=900);
      };
   }
}



