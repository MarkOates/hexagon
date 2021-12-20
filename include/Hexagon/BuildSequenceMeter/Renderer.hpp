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
         std::vector<std::pair<std::string, std::string>> stages;
         float meter_width;
         float meter_height;

      public:
         Renderer(AllegroFlare::FontBin* font_bin=nullptr, std::string status="not_started", std::vector<std::pair<std::string, std::string>> stages={}, float meter_width=90, float meter_height=690);
         ~Renderer();

         void render();
         void draw_rectangle(float x=0, float y=0, float w=1, float h=1, std::string status="incomplete");
         ALLEGRO_COLOR build_color_from_status(std::string status="status_unset");
         ALLEGRO_FONT* obtain_font();
      };
   }
}



