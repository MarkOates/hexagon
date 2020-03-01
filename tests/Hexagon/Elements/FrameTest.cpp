
#include <gtest/gtest.h>

#include <Hexagon/Elements/Frame.hpp>

TEST(Hexagon_Elements_FrameTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Frame frame;
}

TEST(Hexagon_Elements_FrameTest, run__returns_the_expected_response)
{
   Hexagon::Elements::Frame frame;
   //EXPECT_EQ(void, frame.render());
}
