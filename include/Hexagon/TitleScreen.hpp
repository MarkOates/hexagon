#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace Hexagon
{
   class TitleScreen
   {
   private:
      AllegroFlare::FontBin* font_bin;

   public:
      TitleScreen(AllegroFlare::FontBin* font_bin=nullptr);
      ~TitleScreen();


   void draw_hexagon_logo_and_wait_for_keypress(int display_width=1, int display_height=1);
   std::string build_allegro_version_string();
   };
}



