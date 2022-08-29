#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_color.h>
#include <string>
#include <utility>
#include <vector>


namespace Hexagon
{
   namespace BuildSequenceMeter
   {
      class Renderer
      {
      private:
         AllegroFlare::FontBin* font_bin;
         std::string status;
         std::vector<std::tuple<std::string, std::string, std::string, std::string>> stages;
         float meter_width;
         float meter_height;
         ALLEGRO_COLOR backfill_color;
         ALLEGRO_COLOR base_text_color;
         bool draw_frame;

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, std::string status="not_started", std::vector<std::tuple<std::string, std::string, std::string, std::string>> stages={}, float meter_width=90, float meter_height=690, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2}, ALLEGRO_COLOR base_text_color=ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0});
         ~Renderer();

         void set_backfill_color(ALLEGRO_COLOR backfill_color);
         void set_base_text_color(ALLEGRO_COLOR base_text_color);
         void set_draw_frame(bool draw_frame);
         ALLEGRO_COLOR get_backfill_color() const;
         ALLEGRO_COLOR get_base_text_color() const;
         bool get_draw_frame() const;
         void render();
         void draw_build_dump_report_legacy(float width=0, std::string stage_text_dump="[unset-stage_text_dump]");
         void draw_build_dump_report(float width=0, std::string stage_text_dump="[unset-stage_text_dump]");
         void draw_status_box(float x=0, float y=0, float w=1, float h=1, std::string status="incomplete", std::string label="-  -");
         bool is_status_to_draw_label(std::string status="status_unset");
         ALLEGRO_COLOR build_color_from_status(std::string status="status_unset");
         ALLEGRO_FONT* obtain_dump_font();
         ALLEGRO_FONT* obtain_font();
      };
   }
}



