#pragma once


#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>


namespace Hexagon
{
   class Logo
   {
   private:
      float x;
      float y;
      float radius;
      ALLEGRO_FONT* font;
      ALLEGRO_COLOR color;
      float thickness;

   public:
      Logo(float x=0, float y=0, float radius=0, ALLEGRO_FONT* font=nullptr, ALLEGRO_COLOR color=default_color(), float thickness=0);
      ~Logo();


   static ALLEGRO_COLOR default_color();
   void render();
   };
}



