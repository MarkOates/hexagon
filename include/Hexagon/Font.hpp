#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   class Font
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::string font_filename;
      int font_size;

   public:
      Font(AllegroFlare::FontBin* font_bin=nullptr, std::string font_filename="Eurostile.ttf", int font_size=-16);
      ~Font();

      void set_font_filename(std::string font_filename);
      void set_font_size(int font_size);

      std::string get_font_filename();
      int get_font_size();
   ALLEGRO_FONT* al_font();
   };
}



