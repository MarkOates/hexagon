
#include <gtest/gtest.h>

#include <Hexagon/Frame.hpp>

TEST(Hexagon_FrameTest, can_be_created_without_blowing_up)
{
   Hexagon::Frame frame;
}

TEST(Hexagon_FrameTest, run__returns_the_expected_response)
{
   Hexagon::Frame frame;
   //EXPECT_EQ(void, frame.render());
}
