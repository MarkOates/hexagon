#pragma once


#include <AllegroFlare/FontBin.hpp>


namespace Hexagon
{
   namespace BuildSequenceMeter
   {
      class Renderer
      {
      private:
         AllegroFlare::FontBin* font_bin;

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr);
         ~Renderer();


      void render();
      };
   }
}



