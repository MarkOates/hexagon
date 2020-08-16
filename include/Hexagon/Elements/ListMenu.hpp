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
         int cursor;
         std::vector<std::tuple<std::string, std::string>> list_items;

      public:
         ListMenu(AllegroFlare::FontBin* font_bin=nullptr);
         ~ListMenu();


      bool move_cursor_up();
      bool move_cursor_down();
      void render();
      ALLEGRO_FONT* obtain_list_item_font();
      };
   }
}



