#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace Hexagon
{
   class Font
   {
   private:
      AllegroFlare::FontBin* font_bin;

   public:
      Font();
      ~Font();


   std::string run();
   };
}



