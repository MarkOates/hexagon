#pragma once


#include <string>
#include <utility>
#include <vector>


namespace Hexagon
{
   class DirtyGrid
   {
   private:
      std::vector<std::pair<int, int>> dirty_cells;

   public:
      DirtyGrid();
      ~DirtyGrid();


   std::string run();
   };
}



