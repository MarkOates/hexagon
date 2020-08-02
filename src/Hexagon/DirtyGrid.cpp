

#include <Hexagon/DirtyGrid.hpp>
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


