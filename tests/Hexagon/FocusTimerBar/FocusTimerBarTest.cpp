
#include <gtest/gtest.h>

#include <Hexagon/FocusTimerBar/FocusTimerBar.hpp>


#define FLOATING_POINT_ERROR_MARGIN (0.00001f)


TEST(Hexagon_FocusTimerBar_FocusTimerBarTest, can_be_created_without_blowing_up)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
}

TEST(Hexagon_FocusTimerBarTest, has_the_expected_getters_with_the_expected_defaults)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
   EXPECT_EQ(0, focus_timer_bar.get_focus_timer_started_at());
   EXPECT_EQ(1800.0f, focus_timer_bar.get_focus_timer_duration_sec());
   EXPECT_EQ(1800.0f - 300.0f, focus_timer_bar.get_warning_position_sec());
}

TEST(Hexagon_FocusTimerBarTest,
   calc_warning_position_normalized__will_return_the_normalized_time_of_the_warning_position_to_the_bar_duration)
{
   Hexagon::FocusTimerBar::FocusTimerBar focus_timer_bar;
   EXPECT_NEAR(0.8333333f, focus_timer_bar.calc_warning_position_normalized(), FLOATING_POINT_ERROR_MARGIN);
}

