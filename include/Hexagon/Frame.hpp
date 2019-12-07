#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace Hexagon
{
   class Frame
   {
   private:
      static AllegroFlare::FontBin dummy_font_bin;
      AllegroFlare::FontBin& fonts;
      std::string title_text;
      float screen_width;
      float screen_height;

   public:
      Frame();
      ~Frame();


   static AllegroFlare::FontBin& get_dummy_font_bin();
   void render();
   };
}



