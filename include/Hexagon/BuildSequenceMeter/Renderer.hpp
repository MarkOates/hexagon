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
         bool draw_frame;

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, std::string status="not_started", std::vector<std::tuple<std::string, std::string, std::string, std::string>> stages={}, float meter_width=90, float meter_height=690);
         ~Renderer();

         void set_draw_frame(bool draw_frame);
         bool get_draw_frame();
         void render();
         void draw_status_box(float x=0, float y=0, float w=1, float h=1, std::string status="incomplete", std::string label="-  -");
         bool is_status_to_draw_label(std::string status="status_unset");
         ALLEGRO_COLOR build_color_from_status(std::string status="status_unset");
         ALLEGRO_FONT* obtain_font();
      };
   }
}



