#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class Renderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string quote;

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~Renderer();

         void render();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



