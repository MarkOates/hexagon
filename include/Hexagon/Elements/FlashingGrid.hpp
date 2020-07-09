#pragma once


#include <allegro_flare/placement3d.h>


namespace Hexagon
{
   namespace Elements
   {
      class FlashingGrid
      {
      private:
         placement3d place;
         int num_columns;
         int num_rows;
         int box_size;

      public:
         FlashingGrid(placement3d place=placement3d(), int num_columns=16, int num_rows=12, int box_size=10);
         ~FlashingGrid();


      void render();
      };
   }
}



