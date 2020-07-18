
#include <gtest/gtest.h>

#include <Hexagon/Elements/SingleBlockBarGraph.hpp>

TEST(Hexagon_Elements_SingleBlockBarGraphTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
}

TEST(Hexagon_Elements_SingleBlockBarGraphTest, run__returns_the_expected_response)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, single_block_bar_graph.run());
}
