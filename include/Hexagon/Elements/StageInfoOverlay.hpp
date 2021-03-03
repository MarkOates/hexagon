#pragma once


#include <AllegroFlare/FontBin.hpp>
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
         AllegroFlare::FontBin* font_bin;
         ALLEGRO_COLOR* backfill_color;
         float backfill_opacity;
         placement3d* place;
         std::string text;
         bool upcase;

      public:
         StageInfoOverlay(AllegroFlare::FontBin* font_bin=nullptr, ALLEGRO_COLOR* backfill_color=nullptr, float backfill_opacity=1.0f, placement3d* place=nullptr);
         ~StageInfoOverlay();

         void set_place(placement3d* place);
         void set_text(std::string text);
         void set_upcase(bool upcase);
         ALLEGRO_COLOR* get_backfill_color();
         float get_backfill_opacity();
         placement3d* get_place();
         std::string get_text();
         bool get_upcase();
         void render();
         ALLEGRO_FONT* obtain_title_font();
      };
   }
}



