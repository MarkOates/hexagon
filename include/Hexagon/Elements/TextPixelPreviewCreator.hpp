#pragma once


#include <allegro5/allegro.h>


namespace Hexagon
{
   namespace Elements
   {
      class TextPixelPreviewCreator
      {
      private:
         int width;

      public:
         TextPixelPreviewCreator(int width=120);
         ~TextPixelPreviewCreator();


      ALLEGRO_BITMAP* create();
      };
   }
}



