#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class Pill
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         Pill(AllegroFlare::FontBin* font_bin=nullptr);
         ~Pill();

         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



