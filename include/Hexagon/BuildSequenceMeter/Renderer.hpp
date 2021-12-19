#pragma once


#include <AllegroFlare/FontBin.hpp>
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
         Renderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~Renderer();

         void render();
         void render_rectangle(std::string status="incomplete");
      };
   }
}



