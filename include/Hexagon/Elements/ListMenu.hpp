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
         bool title_upcase;
         bool menu_items_upcase;
         int width;
         bool active;
         float padding;

      public:
         ListMenu(AllegroFlare::FontBin* font_bin=nullptr, std::string title="+", std::vector<std::tuple<std::string, std::string>> list_items={}, ALLEGRO_COLOR color=ALLEGRO_COLOR{1.0f, 0.0f, 0.0f, 1.0f});
         ~ListMenu();

         void set_color(ALLEGRO_COLOR color);
         void set_wrap_cursor_when_moving_cursor_outside_bounds(bool wrap_cursor_when_moving_cursor_outside_bounds);
         void set_title_upcase(bool title_upcase);
         void set_menu_items_upcase(bool menu_items_upcase);
         void set_width(int width);
         void set_active(bool active);
         ALLEGRO_COLOR get_color();
         bool get_wrap_cursor_when_moving_cursor_outside_bounds();
         bool get_title_upcase();
         bool get_menu_items_upcase();
         int get_width();
         bool get_active();
         float get_padding();
         bool move_cursor_up();
         bool move_cursor_down();
         std::string get_current_list_item_identifier();
         void render();
         ALLEGRO_FONT* obtain_list_item_font();
         ALLEGRO_FONT* obtain_title_font();
         ALLEGRO_COLOR build_inactive_color();
         void draw_cursor_pointer_arrow(float cpx=1000, float cpy=900);
      };
   }
}



