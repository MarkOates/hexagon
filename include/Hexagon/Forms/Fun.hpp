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
         std::string buffer;

      protected:


      public:
         Fun();
         ~Fun();

         std::string get_buffer() const;
         void draw(placement3d place={}, ALLEGRO_COLOR backfill_color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
         int process_char_input(char input_ch=0);
      };
   }
}



