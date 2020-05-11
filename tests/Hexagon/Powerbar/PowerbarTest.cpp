
#include <gtest/gtest.h>

#include <Hexagon/Powerbar/Powerbar.hpp>

TEST(Hexagon_Powerbar_PowerbarTest, can_be_created_without_blowing_up)
{
   Hexagon::Powerbar::Powerbar powerbar;
}

TEST(Hexagon_Powerbar_PowerbarTest, focus_timer_duration_sec__has_a_default_value_of_20_minutes)
{
   Hexagon::Powerbar::Powerbar powerbar;
   ASSERT_EQ(1200.0f, powerbar.get_focus_timer_duration_sec());
}

