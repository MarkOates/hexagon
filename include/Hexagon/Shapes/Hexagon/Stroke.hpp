#pragma once


#include <allegro5/allegro_color.h>


namespace Hexagon
{
   namespace Shapes
   {
      namespace Hexagon
      {
         class Stroke
         {
         private:
            float start;
            float end;
            ALLEGRO_COLOR color;
            float thickness;

         public:
            Stroke(float start=0, float end=0, ALLEGRO_COLOR color=default_color(), float thickness=1);
            ~Stroke();

            float get_start();
            float get_end();
            ALLEGRO_COLOR get_color();
            float get_thickness();
            static ALLEGRO_COLOR default_color();
         };
      }
   }
}



