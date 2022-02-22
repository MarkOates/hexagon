#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class ComponentTitleSlate
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         ComponentTitleSlate(AllegroFlare::FontBin* font_bin=nullptr);
         ~ComponentTitleSlate();

         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



