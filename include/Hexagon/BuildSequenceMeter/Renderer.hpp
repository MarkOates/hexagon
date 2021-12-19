#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace BuildSequenceMeter
   {
      class Renderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string status;

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, std::string status="not_started");
         ~Renderer();

         void render();
         void render_rectangle(std::string status="incomplete");
         ALLEGRO_FONT* obtain_font();
      };
   }
}



