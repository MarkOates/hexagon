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
         ALLEGRO_STATE previous_render_state;

      public:
         BitmapGridRenderSurface(int num_columns=0, int num_rows=0, int cell_width=1, int cell_height=1);
         ~BitmapGridRenderSurface();


         ALLEGRO_BITMAP* get_surface();
         bool get_initialized();
      void set_cell_width(int cell_width=1);
      void set_cell_height(int cell_height=1);
      void lock_for_render();
      void unlock_for_render();
      void initialize();
      void draw_to_cell(ALLEGRO_BITMAP* bitmap_to_draw=nullptr, ALLEGRO_COLOR tint=ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0}, int x=0, int y=0);
      ALLEGRO_BITMAP* find_sub_bitmap(int x=0, int y=0);
      void destroy();
      };
   }
}



