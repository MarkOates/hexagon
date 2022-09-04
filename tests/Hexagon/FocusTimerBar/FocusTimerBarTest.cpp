
#include <gtest/gtest.h>

#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>

TEST(Hexagon_FocusTimerBar_FocusTimerBarTest, can_be_created_without_blowing_up)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
}

TEST(Hexagon_FocusTimerBarTest, has_the_expected_getters_with_the_expected_defaults)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
   ASSERT_EQ(0, focus_timer_bar.get_focus_timer_started_at());
   ASSERT_EQ(1800.0f, focus_timer_bar.get_focus_timer_duration_sec());
   ASSERT_EQ(1800.0f - 300.0f, focus_timer_bar.get_warning_position_sec());
}

