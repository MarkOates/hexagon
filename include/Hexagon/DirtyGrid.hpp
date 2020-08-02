#pragma once


#include <utility>
#include <vector>


namespace Hexagon
{
   class DirtyGrid
   {
   private:
      int num_columns;
      int num_rows;
      std::vector<std::pair<int, int>> dirty_cells;
      bool initialized;

   public:
      DirtyGrid(int num_columns=0, int num_rows=0);
      ~DirtyGrid();


      bool get_initialized();
      std::vector<std::pair<int, int>> &get_dirty_cells_ref();
   void initialize();
   int dirty_cells_capacity();
   };
}



