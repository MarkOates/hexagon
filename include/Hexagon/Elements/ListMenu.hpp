#pragma once


#include <AllegroFlare/FontBin.hpp>
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
         std::vector<std::tuple<std::string, std::string>> list_items;
         int cursor;

      public:
         ListMenu(AllegroFlare::FontBin* font_bin=nullptr, std::vector<std::tuple<std::string, std::string>> list_items={});
         ~ListMenu();


      bool move_cursor_up();
      bool move_cursor_down();
      void render();
      ALLEGRO_FONT* obtain_list_item_font();
      };
   }
}



