#pragma once




namespace Hexagon
{
   namespace Elements
   {
      class FlashingGrid
      {
      private:
         float width;
         float height;
         int num_columns;
         int num_rows;
         int box_size;
         int counter;

      protected:


      public:
         FlashingGrid(float width=1.0, float height=1.0, int num_columns=16, int num_rows=12, int box_size=10);
         ~FlashingGrid();

         void set_counter(int counter);
         void render();
      };
   }
}



