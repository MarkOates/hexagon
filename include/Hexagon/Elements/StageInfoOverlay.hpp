#pragma once


#include <allegro5/allegro_color.h>
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
         ALLEGRO_COLOR* backfill_color;
         float backfill_opacity;
         placement3d* place;
         std::string text;

      public:
         StageInfoOverlay(ALLEGRO_FONT* title_font=nullptr, ALLEGRO_COLOR* backfill_color=nullptr, float backfill_opacity=1.0f, placement3d* place=nullptr);
         ~StageInfoOverlay();

         void set_place(placement3d* place);
         void set_text(std::string text);

         ALLEGRO_FONT* get_title_font();
         ALLEGRO_COLOR* get_backfill_color();
         float get_backfill_opacity();
         placement3d* get_place();
         std::string get_text();
      void render();
      };
   }
}



