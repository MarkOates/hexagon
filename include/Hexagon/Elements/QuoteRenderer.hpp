#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <Hexagon/Font.hpp>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class QuoteRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         Hexagon::Font font;
         std::string quote;
         std::string speaker;

      public:
         QuoteRenderer(AllegroFlare::FontBin* font_bin=nullptr, std::string quote={}, std::string speaker={});
         ~QuoteRenderer();


      void render();
      };
   }
}



