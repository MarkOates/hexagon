#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace Hexagon
{
   class Frame
   {
   private:
      FontBin& fonts;
      std::string title_text;

   public:
      Frame();
      ~Frame();


   void render();
   };
}



