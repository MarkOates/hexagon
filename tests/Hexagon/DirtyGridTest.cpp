
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

TEST(Hexagon_DirtyGridTest, build_vector__will_return_a_vector_of_the_elements_in_dirty_cells)
{
   Hexagon::DirtyGrid dirty_grid;

   dirty_grid.mark_as_dirty(3, 5);
   dirty_grid.mark_as_dirty(7, 13);

   std::vector<std::pair<int, int>> expected_dirty_cells_as_vector = { {3, 5}, { 7, 13} };
   std::vector<std::pair<int, int>> actual_dirty_cells_as_vector = dirty_grid.build_vector();

   ASSERT_EQ(expected_dirty_cells_as_vector, actual_dirty_cells_as_vector);
}

