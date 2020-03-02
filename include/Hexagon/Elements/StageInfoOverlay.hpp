#pragma once


#include <allegro5/allegro_font.h>
#include <allegro_flare/placement3d.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class StageInfoOverlay
      {
      private:
         ALLEGRO_FONT* title_font;
         placement3d* place;
         std::string text;

      public:
         StageInfoOverlay(ALLEGRO_FONT* title_font=nullptr, placement3d* place=nullptr);
         ~StageInfoOverlay();

         void set_place(placement3d* place);
         void set_text(std::string text);

         ALLEGRO_FONT* get_title_font();
         placement3d* get_place();
         std::string get_text();
      void render();
      };
   }
}



