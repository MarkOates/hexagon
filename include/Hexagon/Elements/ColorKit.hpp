#pragma once


#include <allegro5/allegro_color.h>


namespace Hexagon
{
   namespace Elements
   {
      class ColorKit
      {
      private:
         ALLEGRO_COLOR backfill_color;
         ALLEGRO_COLOR base_text_color;

      public:
         ColorKit(ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f,0.0f,0.0f,1.0f}, ALLEGRO_COLOR base_text_color=ALLEGRO_COLOR{1.0f,1.0f,1.0f,1.0f});
         ~ColorKit();

         void set_backfill_color(ALLEGRO_COLOR backfill_color);
         void set_base_text_color(ALLEGRO_COLOR base_text_color);
         ALLEGRO_COLOR get_backfill_color(float opacity=1.0f);
         ALLEGRO_COLOR get_base_text_color(float opacity=1.0f);
         ALLEGRO_COLOR pure_white_blue();
         ALLEGRO_COLOR black();
         ALLEGRO_COLOR white();
         ALLEGRO_COLOR terminal_warm_orange();
         ALLEGRO_COLOR turn_on_all_the_house_lights_white();
         ALLEGRO_COLOR backwall_gray();
         ALLEGRO_COLOR inv_base_text_color();
         ALLEGRO_COLOR inv_backfill_color();
      };
   }
}



