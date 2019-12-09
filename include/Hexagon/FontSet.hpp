#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <map>
#include <string>


namespace Hexagon
{
   class FontSet
   {
   private:
      std::map<std::string, std::string> font_dictionary;
      static AllegroFlare::FontBin dummy_font_bin;
      AllegroFlare::FontBin& fonts;

   public:
      FontSet();
      ~FontSet();


   static AllegroFlare::FontBin& get_dummy_font_bin();
   ALLEGRO_FONT* obtain_font(std::string identifier="dummy_font");
   };
}



