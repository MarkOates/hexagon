
#include <gtest/gtest.h>

#include <Hexagon/Hud.hpp>

TEST(Hexagon_HudTest, can_be_created_without_blowing_up)
{
   Hexagon::Hud hud;
}

TEST(Hexagon_HudTest, notifications2__has_a_getter_and_setter)
{
   Hexagon::Hud hud;
   ASSERT_EQ(true, hud.get_notifications2().empty());
}

