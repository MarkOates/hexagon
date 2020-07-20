
#include <gtest/gtest.h>

#include <Hexagon/Layout.hpp>

TEST(Hexagon_LayoutTest, can_be_created_without_blowing_up)
{
   Hexagon::Layout layout;
}

TEST(Hexagon_LayoutTest, run__returns_the_expected_response)
{
   Hexagon::Layout layout;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, layout.run());
}
