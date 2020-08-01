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
         int num_columns;
         int num_rows;
         int cell_width;
         int cell_height;
         ALLEGRO_BITMAP* surface;

      public:
         BitmapGridRenderSurface(int num_columns=0, int num_rows=0, int cell_width=1, int cell_height=1);
         ~BitmapGridRenderSurface();


         ALLEGRO_BITMAP* get_surface();
      std::string run();
      };
   }
}



