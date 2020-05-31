
#include <gtest/gtest.h>

#include <Hexagon/System/System.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

TEST(Hexagon_System_System, can_be_created_without_blowing_up)
{
   System system;
}

TEST(DISABLED_Hexagon_System_System, initialize__will_initialize_the_config)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   System system(display);
   system.initialize();
   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_System, get_default_camera_stepback__returns_the_expected_value)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   System system(display);

   EXPECT_EQ(60, system.get_default_camera_stepback());
   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_System, get_default_code_editor_stage_width__returns_the_expected_value)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   System system(display);
   system.initialize();

   EXPECT_EQ(1235, system.get_default_code_editor_stage_width());
   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_System,
   create_two_or_three_split_layout_from_last_component_navigator_selection__will_set_the_hud_title)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   System system(display);

   std::string expected_error_message = "[6System::create_two_or_three_split_layout_from_last_component_" \
                            "navigator_selection error:] guard not met: last_component_navigator_selection " \
                            "cannot be empty";

   ASSERT_THROW_WITH_MESSAGE(
      system.create_two_or_three_split_layout_from_last_component_navigator_selection(),
      std::runtime_error,
      expected_error_message);
   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_System,
   get_all_code_editor_stages__returns_a_list_of_all_the_code_editor_stages)
{
}

TEST(DISABLED_Hexagon_System_System,
   enable_drawing_info_overlays_on_all_code_editor_stages)
{
   std::vector<::CodeEditor::CodeEditor *> stages;

   System system(nullptr);
   system.initialize();
   EXPECT_EQ(true, system.enable_drawing_info_overlays_on_all_code_editor_stages());

   //TODO: check outcomes of this operation

   al_uninstall_system();
}

TEST(DISABLED_Hexagon_System_System,
   refresh_git_modified_line_numbers_on_all_code_editor_stages__will_do_that)
{
}

