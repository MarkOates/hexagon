#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class QuoteRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         QuoteRenderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~QuoteRenderer();


      void render();
      ALLEGRO_FONT* obtain_quote_font();
      };
   }
}



