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
      int font_size;

   public:
      Font();
      ~Font();

      void set_font_filename(std::string font_filename);
      void set_font_size(int font_size);

      std::string get_font_filename();
      int get_font_size();
   };
}



