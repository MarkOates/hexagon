
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/StageFactory.hpp>

TEST(Hexagon_StageFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::StageFactory stage_factory;
}

TEST(Hexagon_StageFactoryTest, create__returns_the_expected_response)
{
   Hexagon::StageFactory stage_factory;
   EXPECT_EQ(nullptr, stage_factory.create());
}

TEST(Hexagon_StageFactoryTest, get_current_display__when_allegro_is_not_initialized__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::get_current_display: error: guard " \
                                        "\"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_factory.get_current_display(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_StageFactoryTest, get_current_display__returns_the_current_display)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::StageFactory stage_factory;
   ALLEGRO_DISPLAY *expected_display = display;
   ASSERT_EQ(display, stage_factory.get_current_display());

   al_destroy_display(display);
   al_uninstall_system();
}

