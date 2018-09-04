#pragma once


#include <allegro5/allegro_color.h>


namespace Hexagon
{
   class Logo
   {
   private:
      float x;
      float y;
      float radius;
      ALLEGRO_COLOR color;
      float thickness;

   public:
      Logo(float x, float y, float radius, ALLEGRO_COLOR color, float thickness);

      void render();
   };
};


