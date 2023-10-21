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
         ALLEGRO_COLOR backfill_color;
         float backfill_opacity;
         int cursor;
         float frame_offset_y;
         bool wrap_cursor_when_moving_cursor_outside_bounds;
         bool title_upcase;
         bool menu_items_upcase;
         int width;
         bool active;
         float padding;
         ALLEGRO_FONT* obtain_list_item_font();
         ALLEGRO_FONT* obtain_title_font();
         void draw_cursor_pointer_arrow(float cpx=1000, float cpy=900);

      protected:


      public:
         ListMenu(AllegroFlare::FontBin* font_bin=nullptr, std::string title="+", std::vector<std::tuple<std::string, std::string>> list_items={}, ALLEGRO_COLOR color=ALLEGRO_COLOR{1.0f, 0.0f, 0.0f, 1.0f}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0, 0, 0, 1}, float backfill_opacity=0.9f);
         ~ListMenu();

         void set_color(ALLEGRO_COLOR color);
         void set_backfill_color(ALLEGRO_COLOR backfill_color);
         void set_backfill_opacity(float backfill_opacity);
         void set_wrap_cursor_when_moving_cursor_outside_bounds(bool wrap_cursor_when_moving_cursor_outside_bounds);
         void set_title_upcase(bool title_upcase);
         void set_menu_items_upcase(bool menu_items_upcase);
         void set_width(int width);
         void set_active(bool active);
         std::vector<std::tuple<std::string, std::string>> get_list_items() const;
         ALLEGRO_COLOR get_color() const;
         ALLEGRO_COLOR get_backfill_color() const;
         float get_backfill_opacity() const;
         bool get_wrap_cursor_when_moving_cursor_outside_bounds() const;
         bool get_title_upcase() const;
         bool get_menu_items_upcase() const;
         int get_width() const;
         bool get_active() const;
         float get_padding() const;
         void set_list_items(std::vector<std::tuple<std::string, std::string>> list_items={});
         bool move_cursor_up();
         bool move_cursor_down();
         std::string get_current_list_item_identifier();
         void render();
         ALLEGRO_COLOR build_inactive_color();
         ALLEGRO_COLOR build_opacified_backfill_color();
      };
   }
}



