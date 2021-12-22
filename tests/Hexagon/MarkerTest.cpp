
#include <gtest/gtest.h>

#include <Hexagon/Marker.hpp>

TEST(Hexagon_MarkerTest, can_be_created_without_blowing_up)
{
   Hexagon::Marker marker;
}

TEST(Hexagon_MarkerTest, run__returns_the_expected_response)
{
   Hexagon::Marker marker;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, marker.run());
}
