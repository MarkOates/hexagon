
#include <gtest/gtest.h>

#include <Hexagon/DirtyGrid.hpp>

TEST(Hexagon_DirtyGridTest, can_be_created_without_blowing_up)
{
   Hexagon::DirtyGrid dirty_grid;
}

TEST(Hexagon_DirtyGridTest, initialize__reserves_the_expected_number_of_dirty_cells_and_sets_initialized_to_true)
{
   Hexagon::DirtyGrid dirty_grid(8, 8+1);

   EXPECT_EQ(false, dirty_grid.get_initialized());
   EXPECT_EQ(0, dirty_grid.dirty_cells_capacity());

   dirty_grid.initialize();

   EXPECT_EQ(true, dirty_grid.get_initialized());
   EXPECT_GT(dirty_grid.dirty_cells_capacity(), 64);
}


