#pragma once


#include <allegro5/allegro.h>
#include <vector>


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
         std::vector<ALLEGRO_BITMAP*> cell_sub_bitmaps;
         bool initialized;

      public:
         BitmapGridRenderSurface(int num_columns=0, int num_rows=0, int cell_width=1, int cell_height=1);
         ~BitmapGridRenderSurface();


         ALLEGRO_BITMAP* get_surface();
         bool get_initialized();
      void initialize();
      void draw_to_surface(ALLEGRO_BITMAP* bitmap=nullptr, int x=0, int y=0);
      ALLEGRO_BITMAP* get_sub_bitmap(int x=0, int y=0);
      void destroy();
      };
   }
}



