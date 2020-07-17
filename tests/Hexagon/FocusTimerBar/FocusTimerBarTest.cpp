
#include <gtest/gtest.h>

#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>

TEST(Hexagon_FocusTimerBar_FocusTimerBarTest, can_be_created_without_blowing_up)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
}

TEST(Hexagon_FocusTimerBar_FocusTimerBarTest, run__returns_the_expected_response)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, focus_timer_bar.run());
}
