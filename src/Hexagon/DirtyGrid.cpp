

#include <Hexagon/DirtyGrid.hpp>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <utility>


namespace Hexagon
{


DirtyGrid::DirtyGrid()
   : dirty_cells({})
{
}


DirtyGrid::~DirtyGrid()
{
}


std::set<std::pair<int, int>> DirtyGrid::get_dirty_cells()
{
   return dirty_cells;
}


void DirtyGrid::mark_as_dirty(int x, int y)
{
dirty_cells.insert(std::pair<int, int>{x, y});
return;

}

void DirtyGrid::mark_row_as_dirty(int row, int start, int length)
{
for (int x=start; x<(start + length); x++)
{
   dirty_cells.insert(std::pair<int, int>{x, row});
}
return;

}

void DirtyGrid::incorporate(Hexagon::DirtyGrid* other_dirty_grid)
{
if (!(other_dirty_grid))
   {
      std::stringstream error_message;
      error_message << "DirtyGrid" << "::" << "incorporate" << ": error: " << "guard \"other_dirty_grid\" not met";
      throw std::runtime_error(error_message.str());
   }
dirty_cells.insert(other_dirty_grid->dirty_cells.begin(), other_dirty_grid->dirty_cells.end());
return;

}

std::vector<std::pair<int, int>> DirtyGrid::build_vector()
{
std::vector<std::pair<int, int>> result;
result.reserve(dirty_cells.size());
for (auto it=dirty_cells.begin(); it!=dirty_cells.end(); )
{
   result.push_back(std::move(dirty_cells.extract(it++).value()));
}
return result;

}

void DirtyGrid::clear()
{
dirty_cells.clear();
return;

}
} // namespace Hexagon


