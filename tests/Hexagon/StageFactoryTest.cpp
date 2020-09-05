
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/StageFactory.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>

TEST(Hexagon_StageFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::StageFactory stage_factory;
}

TEST(Hexagon_StageFactoryTest, create__returns_the_expected_response)
{
   Hexagon::StageFactory stage_factory;
   EXPECT_EQ(nullptr, stage_factory.create());
}

TEST(Hexagon_StageFactoryTest, obtain_default_navigator_directory__without_a_config__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::obtain_default_navigator_directory: error: guard " \
                                        "\"config\" not met";
   ASSERT_THROW_WITH_MESSAGE(
      stage_factory.create_advanced_component_navigator(),
      std::runtime_error,
      expected_error_message
   );
}

TEST(Hexagon_StageFactoryTest, obtain_base_text_color__without_a_config__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::obtain_base_text_color: error: guard \"config\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_factory.obtain_base_text_color(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_StageFactoryTest,
   create_advanced_component_navigator__creates_an_advanced_component_navigator_with_the_expected_properties)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);
   Hexagon::System::Config config;
   config.initialize();
   Hexagon::StageFactory stage_factory(&config);
   StageInterface *created_stage = stage_factory.create_advanced_component_navigator();
   Hexagon::AdvancedComponentNavigator::Stage *stage =
      static_cast<Hexagon::AdvancedComponentNavigator::Stage*>(created_stage);

   StageInterface::type_t expected_type = StageInterface::COMPONENT_NAVIGATOR;
   StageInterface::type_t actual_type = created_stage->get_type();

   ASSERT_NE(nullptr, created_stage);
   ASSERT_EQ(expected_type, actual_type);

   ALLEGRO_COLOR expected_base_text_color = config.get_base_text_color();
   ALLEGRO_COLOR actual_base_text_color = stage->get_base_text_color();

   ALLEGRO_COLOR expected_base_backfill_color = config.get_backfill_color();
   ALLEGRO_COLOR actual_base_backfill_color = stage->get_base_backfill_color();

   placement3d expected_place = stage_factory.build_component_navigator_initial_place();
   placement3d actual_place = stage->get_place();

   EXPECT_EQ(true, stage->get_render_on_hud());
   EXPECT_EQ(expected_base_text_color.r, actual_base_text_color.r); // for now, just comparing red component
   EXPECT_EQ(expected_base_backfill_color.r, actual_base_backfill_color.r); // for now, just comparing red component
   EXPECT_EQ(expected_place, actual_place);

   al_destroy_display(display);
   al_uninstall_system();
}

TEST(Hexagon_StageFactoryTest, get_current_display__when_allegro_is_not_initialized__raises_an_exception)
{
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::get_current_display: error: guard " \
                                        "\"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_factory.get_current_display(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_StageFactoryTest, get_current_display__without_a_current_display__raises_an_exception)
{
   al_init();
   Hexagon::StageFactory stage_factory;
   std::string expected_error_message = "StageFactory::get_current_display: error: guard " \
                                        "\"al_get_current_display()\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_factory.get_current_display(), std::runtime_error, expected_error_message);
   al_uninstall_system();
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

TEST(Hexagon_StageFactoryTest, build_component_navigator_initial_place__returns_the_expected_position)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   Hexagon::StageFactory stage_factory;

   vec3d expected_placement_position =
     vec3d(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   placement3d actual_placement = stage_factory.build_component_navigator_initial_place();

   ASSERT_EQ(expected_placement_position, actual_placement.position);

   al_destroy_display(display);
   al_uninstall_system();
}
