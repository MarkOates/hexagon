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
         Frame(float width=1.0f, float height=1.0f);
         ~Frame();

         void set_title_text(std::string title_text);
         void set_width(float width);
         void set_height(float height);

      static AllegroFlare::FontBin& get_dummy_font_bin();
      void render();
      };
   }
}



