#pragma once


#include <Hexagon/FontSet.hpp>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class StageInfoOverlay
      {
      private:
         Hexagon::FontSet* font_set;
         std::string text;

      public:
         StageInfoOverlay();
         ~StageInfoOverlay();


         std::string get_text();
      void render();
      };
   }
}



