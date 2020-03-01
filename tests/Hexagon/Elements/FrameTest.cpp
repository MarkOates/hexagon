
#include <gtest/gtest.h>

#include <Hexagon/Elements/Frame.hpp>

#define FLOATING_POINT_ERROR_MARGIN (0.00001f)

static void EXPECT_EQ_COLOR(ALLEGRO_COLOR expected, ALLEGRO_COLOR actual)
{
   EXPECT_NEAR(expected.r, actual.r, FLOATING_POINT_ERROR_MARGIN);
   EXPECT_NEAR(expected.g, actual.g, FLOATING_POINT_ERROR_MARGIN);
   EXPECT_NEAR(expected.b, actual.b, FLOATING_POINT_ERROR_MARGIN);
   EXPECT_NEAR(expected.a, actual.a, FLOATING_POINT_ERROR_MARGIN);
}

TEST(Hexagon_Elements_FrameTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Frame frame;
}

TEST(Hexagon_Elements_FrameTest, run__returns_the_expected_response)
{
   Hexagon::Elements::Frame frame;
   //EXPECT_EQ(void, frame.render());
}

TEST(Hexagon_Elements_FrameTest, build_default_frame_color__builds_the_expected_color)
{
   ALLEGRO_COLOR expected_color = al_map_rgba_f(0.408, 0.476, 0.451, 0.51);
   ALLEGRO_COLOR actual_color = Hexagon::Elements::Frame::build_default_frame_color();

   EXPECT_EQ_COLOR(expected_color, actual_color);
}
