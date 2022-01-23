#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace ObjectivesLog
   {
      class ObjectiveRenderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         ObjectiveRenderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~ObjectiveRenderer();

         void render();
         ALLEGRO_FONT* obtain_quote_font();
      };
   }
}



