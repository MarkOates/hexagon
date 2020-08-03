#pragma once


#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class QuoteRenderer
      {
      private:
         std::string quote;

      public:
         QuoteRenderer();
         ~QuoteRenderer();


      void render();
      ALLEGRO_FONT* obtain_quote_font();
      };
   }
}



