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

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~Renderer();

         void render();
         void render_menu_item(float x=0, float y=0, std::string input="^H", std::string label="Unlabeled");
         ALLEGRO_FONT* obtain_font();
      };
   }
}



