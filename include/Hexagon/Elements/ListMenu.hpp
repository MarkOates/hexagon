#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class ListMenu
      {
      private:
         AllegroFlare::FontBin* font_bin;

      public:
         ListMenu(AllegroFlare::FontBin* font_bin=nullptr);
         ~ListMenu();


      std::string run();
      };
   }
}



