
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

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

TEST(Hexagon_HudTest, draw_powerbar__has_a_getter_and_is_initialized_with_the_expected_default)
{
   Hexagon::Hud hud;
   ASSERT_EQ(true, hud.get_draw_powerbar());
}

TEST(Hexagon_HudTest, reinitialize__before_initialization__raises_an_error)
{
   Hexagon::Hud hud;
   std::string expected_message = "Hud::reinitialize: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(hud.reinitialize(), std::runtime_error, expected_message);
}

TEST(Hexagon_HudTest, draw__before_initialization__raises_an_error)
{
   Hexagon::Hud hud;
   std::string expected_message = "Hud::draw: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(hud.draw(), std::runtime_error, expected_message);
}

