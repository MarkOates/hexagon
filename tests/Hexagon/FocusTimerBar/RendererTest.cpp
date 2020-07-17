
#include <gtest/gtest.h>

#include <Hexagon/FocusTimerBar/Renderer.hpp>

TEST(Hexagon_FocusTimerBar_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::FocusTimerBar::Renderer renderer;
}

TEST(Hexagon_FocusTimerBar_RendererTest, run__returns_the_expected_response)
{
   Hexagon::FocusTimerBar::Renderer renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, renderer.run());
}
