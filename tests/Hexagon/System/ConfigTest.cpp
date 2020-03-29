
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/System/Config.hpp>

TEST(Hexagon_System_ConfigTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Config config;
}

TEST(Hexagon_System_ConfigTest, get_initial_display_width__without_initialization__throws_an_error)
{
   al_init();
   Hexagon::System::Config config;

   std::string expected_error_message = "[Hexagon::System::Config error:] cannot call " \
                                        "\"get_initial_display_width\". This component must be " \
                                        "initialized before this function can be used.";

   ASSERT_THROW_WITH_MESSAGE(config.get_initial_display_width(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_ConfigTest,
   get_initial_display_width__without_the_config_key_present__returns_the_expected_default_value)
{
   al_init();
   Hexagon::System::Config config;
   config.initialize();

   ASSERT_EQ(2430, config.get_initial_display_width());
}

TEST(Hexagon_System_ConfigTest, get_initial_display_height__without_initialization__throws_an_error)
{
   al_init();
   Hexagon::System::Config config;

   std::string expected_error_message = "[Hexagon::System::Config error:] cannot call " \
                                        "\"get_initial_display_height\". This component must be " \
                                        "initialized before this function can be used.";

   ASSERT_THROW_WITH_MESSAGE(config.get_initial_display_height(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_ConfigTest,
   get_initial_display_height__without_the_config_key_present__returns_the_expected_default_value)
{
   al_init();
   Hexagon::System::Config config;
   config.initialize();

   ASSERT_EQ(1350, config.get_initial_display_height());
}
