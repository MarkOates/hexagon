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
         float width;
         float height;
         ALLEGRO_FONT* obtain_font();

      protected:


      public:
         ComponentTitleSlate(AllegroFlare::FontBin* font_bin=nullptr, std::string quote={}, float width=1, float height=1);
         ~ComponentTitleSlate();

         void render();
      };
   }
}



