#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace Hexagon
{
   class Font
   {
   private:
      AllegroFlare::FontBin* font_bin;
      std::string font_filename;

   public:
      Font();
      ~Font();

      void set_font_filename(std::string font_filename);

      std::string get_font_filename();
   };
}



