#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class Frame
      {
      private:
         static AllegroFlare::FontBin dummy_font_bin;
         AllegroFlare::FontBin& fonts;
         std::string title_text;
         float width;
         float height;

      public:
         Frame();
         ~Frame();


      static AllegroFlare::FontBin& get_dummy_font_bin();
      void render();
      };
   }
}



