
#include <gtest/gtest.h>

#include <Hexagon/MarkerNavigator.hpp>

TEST(Hexagon_MarkerNavigatorTest, can_be_created_without_blowing_up)
{
   Hexagon::MarkerNavigator marker_navigator;
}

TEST(Hexagon_MarkerNavigatorTest, initializes_with_an_empty_index)
{
   Hexagon::MarkerNavigator marker_navigator;
   std::map<std::string, Hexagon::Marker> expected_index = {};
   std::map<std::string, Hexagon::Marker> actual_index = marker_navigator.get_markers_index();

   //ASSERT_EQ(expected_index, actual_index); // TODO test equality
}

TEST(Hexagon_MarkerNavigatorTest, add_or_override__adds_a_marker_to_the_index)
{
   std::map<std::string, Hexagon::Marker> expected_index = {};
}

