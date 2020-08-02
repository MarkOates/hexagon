
#include <gtest/gtest.h>

#include <Hexagon/DirtyGrid.hpp>

TEST(Hexagon_DirtyGridTest, can_be_created_without_blowing_up)
{
   Hexagon::DirtyGrid dirty_grid;
}

TEST(Hexagon_DirtyGridTest, run__returns_the_expected_response)
{
   Hexagon::DirtyGrid dirty_grid;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, dirty_grid.run());
}
