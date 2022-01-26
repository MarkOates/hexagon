#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MultiplexMenuRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         MultiplexMenuRenderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~MultiplexMenuRenderer();

         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



