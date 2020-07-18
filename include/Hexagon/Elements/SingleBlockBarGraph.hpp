#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class SingleBlockBarGraph
      {
      private:
         int number_of_active_bars;
         int number_of_bg_bars;
         float bar_width;
         float bar_height;
         float bar_spacing;
         float stroke_width;
         ALLEGRO_COLOR main_bar_color;
         ALLEGRO_COLOR bg_bar_color;
         ALLEGRO_COLOR stroke_color;

      public:
         SingleBlockBarGraph(int number_of_active_bars=0, int number_of_bg_bars=0, float bar_width=1.0f, float bar_height=1.0f, float bar_spacing=0.0f, float stroke_width=1.0f, ALLEGRO_COLOR main_bar_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f}, ALLEGRO_COLOR bg_bar_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f}, ALLEGRO_COLOR stroke_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
         ~SingleBlockBarGraph();


      std::string run();
      };
   }
}



