
#include <gtest/gtest.h>

#include <Hexagon/Elements/CoolGrid.hpp>

TEST(Hexagon_Elements_CoolGridTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::CoolGrid cool_grid;
}

TEST(Hexagon_Elements_CoolGridTest, run__returns_the_expected_response)
{
   Hexagon::Elements::CoolGrid cool_grid;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, cool_grid.run());
}
