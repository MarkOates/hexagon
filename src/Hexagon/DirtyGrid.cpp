

#include <Hexagon/DirtyGrid.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include <vector>


namespace Hexagon
{


DirtyGrid::DirtyGrid()
   : dirty_cells({})
{
}


DirtyGrid::~DirtyGrid()
{
}


std::set<std::pair<int, int>> DirtyGrid::get_dirty_cells() const
{
   return dirty_cells;
}


int DirtyGrid::dirty_cells_count()
{
   return dirty_cells.size();
}

int DirtyGrid::dirty_cells_empty()
{
   return dirty_cells.empty();
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
      error_message << "[DirtyGrid::mark_all_as_dirty]: error: guard \"lines\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DirtyGrid::mark_all_as_dirty: error: guard \"lines\" not met");
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
      error_message << "[DirtyGrid::incorporate]: error: guard \"other_dirty_grid\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DirtyGrid::incorporate: error: guard \"other_dirty_grid\" not met");
   }
   dirty_cells.insert(other_dirty_grid->dirty_cells.begin(), other_dirty_grid->dirty_cells.end());
   return;
}

std::vector<std::pair<int, int>> DirtyGrid::build_vector()
{
   std::vector<std::pair<int, int>> result;
   result.reserve(dirty_cells.size());
   for (auto it=dirty_cells.begin(); it!=dirty_cells.end(); it++)
   {
      //result.push_back(std::move(dirty_cells.extract(it++).value())); // this line appears to destroy
                                                                        // the original, hopefully the
                                                                        // provided alternative is performant
      result.push_back(*it);
   }
   return result;
}

void DirtyGrid::clear()
{
   dirty_cells.clear();
   return;
}


} // namespace Hexagon


