#pragma once


#include <allegro5/allegro.h>
#include <string>


namespace Hexagon
{
   namespace Elements
   {
      class BitmapGridRenderSurface
      {
      private:
         ALLEGRO_BITMAP* surface;

      public:
         BitmapGridRenderSurface();
         ~BitmapGridRenderSurface();


         ALLEGRO_BITMAP* get_surface();
      std::string run();
      };
   }
}



