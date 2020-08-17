#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Profiler.hpp>
#include <allegro5/allegro_font.h>
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


   void draw_hexagon_logo_and_wait_for_keypress();
   void draw_menu();
   void render_profiler_graph(AllegroFlare::Profiler* profiler=nullptr, ALLEGRO_FONT* font=nullptr);
   std::string build_allegro_version_string();
   };
}



