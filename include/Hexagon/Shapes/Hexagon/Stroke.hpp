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

         protected:


         public:
            Stroke(float start=0, float end=0, ALLEGRO_COLOR color=default_color(), float thickness=1);
            ~Stroke();

            float get_start() const;
            float get_end() const;
            ALLEGRO_COLOR get_color() const;
            float get_thickness() const;
            static ALLEGRO_COLOR default_color();
         };
      }
   }
}



