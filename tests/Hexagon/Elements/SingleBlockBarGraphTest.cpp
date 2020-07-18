
#include <gtest/gtest.h>

#include <Hexagon/Elements/SingleBlockBarGraph.hpp>

TEST(Hexagon_Elements_SingleBlockBarGraphTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
}

TEST(Hexagon_Elements_SingleBlockBarGraphTest, draw__does_not_blow_up)
{
   Hexagon::Elements::SingleBlockBarGraph single_block_bar_graph;
   single_block_bar_graph.draw();
   SUCCEED();
}
