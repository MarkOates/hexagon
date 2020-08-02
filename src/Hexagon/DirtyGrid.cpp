

#include <Hexagon/DirtyGrid.hpp>
#include <stdexcept>
#include <sstream>
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


int DirtyGrid::dirty_cells_count()
{
return dirty_cells.size();

}

void DirtyGrid::mark_as_dirty(int x, int y)
{
dirty_cells.insert(std::pair<int, int>{x, y});
return;

}

void DirtyGrid::mark_all_as_dirty(std::vector<std::string>* lines)
{
if (!(lines))
   {
      std::stringstream error_message;
      error_message << "DirtyGrid" << "::" << "mark_all_as_dirty" << ": error: " << "guard \"lines\" not met";
      throw std::runtime_error(error_message.str());
   }
type: std::vector<std::string>& local_lines_ref = *lines;
for (int l=0; l<local_lines_ref.size(); l++)
{
   mark_row_as_dirty(l, 0, local_lines_ref[l].length());
}
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


