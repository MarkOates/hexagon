#pragma once


#include <allegro5/allegro.h>
#include <allegro_flare/placement3d.h>
#include <string>


namespace Hexagon
{
   namespace Forms
   {
      class Fun
      {
      private:
         placement3d place;
         ALLEGRO_COLOR backfill_color;
         std::string buffer;

      public:
         Fun(placement3d place={}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
         ~Fun();

         void set_place(placement3d place);
         void set_backfill_color(ALLEGRO_COLOR backfill_color);

         placement3d get_place();
         ALLEGRO_COLOR get_backfill_color();
         std::string get_buffer();
      void draw();
      int process_char_input(char input_ch=0);
      };
   }
}



