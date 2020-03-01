#pragma once


#include <allegro5/allegro_font.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class StageInfoOverlay
      {
      private:
         ALLEGRO_FONT* title_font;
         std::string text;

      public:
         StageInfoOverlay(ALLEGRO_FONT* title_font=nullptr);
         ~StageInfoOverlay();


         ALLEGRO_FONT* get_title_font();
         std::string get_text();
      void render();
      };
   }
}



