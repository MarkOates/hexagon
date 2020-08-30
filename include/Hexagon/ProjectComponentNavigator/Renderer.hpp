#pragma once


#include <Hexagon/ProjectComponentNavigator/Stage.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   namespace ProjectComponentNavigator
   {
      class Renderer
      {
      private:
         Hexagon::ProjectComponentNavigator::Stage* stage;
         bool is_focused;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;
         ALLEGRO_COLOR* base_backfill_color;
         float backfill_opacity;
         ALLEGRO_COLOR* base_text_color;
         ALLEGRO_COLOR frame_color;

      public:
         Renderer(Hexagon::ProjectComponentNavigator::Stage* stage=nullptr, bool is_focused=true, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20, ALLEGRO_COLOR* base_backfill_color=nullptr, float backfill_opacity=1.0f, ALLEGRO_COLOR* base_text_color=nullptr);
         ~Renderer();


         ALLEGRO_COLOR* get_base_backfill_color();
         ALLEGRO_COLOR* get_base_text_color();
      ALLEGRO_COLOR build_backfill_color();
      ALLEGRO_COLOR build_text_color();
      ALLEGRO_COLOR build_frame_color();
      void draw_search_text_box();
      void foobar();
      void render();
      void render_raw();
      };
   }
}



