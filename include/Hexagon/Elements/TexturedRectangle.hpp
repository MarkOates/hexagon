#pragma once


#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace Elements
   {
      class TexturedRectangle
      {
      private:
         float x1;
         float y1;
         float x2;
         float y2;
         ALLEGRO_BITMAP* texture;

      protected:


      public:
         TexturedRectangle(float x1=0, float y1=0, float x2=1, float y2=1, ALLEGRO_BITMAP* texture=nullptr);
         ~TexturedRectangle();

         void draw();
      };
   }
}



