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
         placement3d* placement;
         std::string text;

      public:
         StageInfoOverlay(ALLEGRO_FONT* title_font=nullptr, placement3d* placement=nullptr);
         ~StageInfoOverlay();

         void set_placement(placement3d* placement);

         ALLEGRO_FONT* get_title_font();
         placement3d* get_placement();
         std::string get_text();
      void render();
      };
   }
}



