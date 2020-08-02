
#include <gtest/gtest.h>

#include <Hexagon/DirtyGrid.hpp>

TEST(Hexagon_DirtyGridTest, can_be_created_without_blowing_up)
{
   Hexagon::DirtyGrid dirty_grid;
}

TEST(Hexagon_DirtyGridTest, mark_as_dirty__will_include_the_item_in_the_list)
{
   Hexagon::DirtyGrid dirty_grid;
   std::set<std::pair<int, int>> dirty_cells;

   dirty_cells = dirty_grid.get_dirty_cells();
   ASSERT_EQ(0, dirty_cells.size());

   dirty_grid.mark_as_dirty(3, 5);
   dirty_grid.mark_as_dirty(7, 13);

   dirty_cells = dirty_grid.get_dirty_cells();
   ASSERT_EQ(2, dirty_cells.size());
}

