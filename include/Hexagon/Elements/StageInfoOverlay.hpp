#pragma once


#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class StageInfoOverlay
      {
      private:
         std::string text;

      public:
         StageInfoOverlay();
         ~StageInfoOverlay();


         std::string get_text();
      void render();
      };
   }
}



