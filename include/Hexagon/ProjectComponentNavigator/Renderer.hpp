#pragma once


#include <ALLEGRO_FONT.hpp>
#include <Hexagon/ProjectComponentNavigator/Stage.hpp>
#include <allegro5/allegro_color.h>
#include <utility>


namespace Hexagon
{
   namespace ProjectComponentNavigator
   {
      class Renderer
      {
      private:
         Hexagon::ProjectComponentNavigator::Stage* stage;
         ALLEGRO_FONT* font;
         int cell_width;
         int cell_height;
         ALLEGRO_COLOR* base_backfill_color;
         float backfill_opacity;
         ALLEGRO_COLOR* base_text_color;
         float line_stroke_thickness;

      public:
         Renderer(Hexagon::ProjectComponentNavigator::Stage* stage=nullptr, ALLEGRO_FONT* font=nullptr, int cell_width=10, int cell_height=20, ALLEGRO_COLOR* base_backfill_color=nullptr, float backfill_opacity=1.0f, ALLEGRO_COLOR* base_text_color=nullptr);
         ~Renderer();

         ALLEGRO_COLOR* get_base_backfill_color() const;
         ALLEGRO_COLOR* get_base_text_color() const;
         ALLEGRO_COLOR build_backfill_color();
         ALLEGRO_COLOR build_text_color();
         ALLEGRO_COLOR build_frame_color();
         float build_line_height();
         void draw_search_text_box();
         void render();
         void render_window_raw();
         void render_cursor_box_raw();
         void render_window_title_raw();
         std::pair<bool, bool> render_list_elements_raw();
         void render_list_clipping_arrows_raw(bool list_clipping_occurred_above=false, bool list_clipping_occurred_below=false);
         void render_raw();
      };
   }
}



