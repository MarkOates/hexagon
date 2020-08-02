#pragma once


#include <set>
#include <utility>
#include <vector>


namespace Hexagon
{
   class DirtyGrid
   {
   private:
      std::set<std::pair<int, int>> dirty_cells;

   public:
      DirtyGrid();
      ~DirtyGrid();


      std::set<std::pair<int, int>> get_dirty_cells();
   void mark_as_dirty(int x=0, int y=0);
   void incorporate(Hexagon::DirtyGrid* other_dirty_grid=nullptr);
   std::vector<std::pair<int, int>> build_vector();
   void clear();
   };
}



