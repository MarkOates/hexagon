

#include <Hexagon/DirtyGrid.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{


DirtyGrid::DirtyGrid(int num_columns, int num_rows)
   : num_columns(num_columns)
   , num_rows(num_rows)
   , dirty_cells({})
   , initialized(false)
{
}


DirtyGrid::~DirtyGrid()
{
}


bool DirtyGrid::get_initialized()
{
   return initialized;
}


std::vector<std::pair<int, int>> &DirtyGrid::get_dirty_cells_ref()
{
   return dirty_cells;
}


void DirtyGrid::initialize()
{
if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "DirtyGrid" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
dirty_cells.reserve(num_columns * num_rows);
initialized = true;
return;

}

int DirtyGrid::dirty_cells_capacity()
{
return dirty_cells.capacity();

}
} // namespace Hexagon


