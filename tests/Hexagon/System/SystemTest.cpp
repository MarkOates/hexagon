
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Hexagon/System/System.hpp>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

TEST(Hexagon_System_System, can_be_created_without_blowing_up)
{
   Hexagon::System::System system;
}

TEST(Hexagon_System_System, initialize__will_initialize_the_config)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::System::System system(display);
   system.initialize();
   al_uninstall_system();
}

TEST(Hexagon_System_System,
   save_frontmost_code_editor_stage_and_touch_if_symlink__will_run_builds_if_the_frontmost_stage_is_a_code_editor_type)
{
   // TODO
}

TEST(Hexagon_System_System, get_default_code_editor_stage_width__returns_the_expected_value)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::System::System system(display);
   system.initialize();

   EXPECT_EQ(1235, system.get_default_code_editor_stage_width());
   al_uninstall_system();
}

TEST(Hexagon_System_System,
   DISABLED_create_two_or_three_split_layout_from_last_component_navigator_selection__will_set_the_hud_title)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   Hexagon::System::System system(display);

   std::string expected_error_message = "[6System::create_two_or_three_split_layout_from_last_component_" \
                            "navigator_selection error:] guard not met: last_component_navigator_selection " \
                            "cannot be empty";

   ASSERT_THROW_WITH_MESSAGE(
      system.create_two_or_three_split_layout_from_last_component_navigator_selection(),
      std::runtime_error,
      expected_error_message);
   al_uninstall_system();
}

TEST(Hexagon_System_System,
   DISABLED_create_stages_from_layout_of_last_component_navigator_selection__will_create_the_expected_layout)
{
   std::string project_directory = "/Users/markoates/Repos/hexagon/tests/fixtures/FixtureProject";
   std::string component_name = "FixtureObjectThing";
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);
   Hexagon::System::System system(display);

   system.initialize();

   system.set_option__saving_focused_filename_to_file_is_disabled(true);
   system.set_current_project_directory(project_directory);
   system.set_last_component_navigator_selection(component_name);

   system.create_stages_from_layout_of_last_component_navigator_selection();
   std::vector<Hexagon::CodeEditor::Stage *> stages = system.get_all_code_editor_stages();

   ASSERT_EQ(2, stages.size());

   al_uninstall_system();
}

TEST(Hexagon_System_System,
   create_stages_from_layout_of_last_component_navigator_selection__will_set_the_focused_component_name)
{
   // TODO
}

TEST(Hexagon_System_System,
   create_stages_from_layout_of_last_component_navigator_selection__will_set_the_hud_title)
{
   // TODO
}

TEST(Hexagon_System_System,
   enable_drawing_info_overlays_on_all_code_editor_stages__sets_the_expected_property_on_all_the_expected_stages)
{
   // TODO
}

TEST(Hexagon_System_System,
   save_frontmost_code_editor_stage__will_save_the_stage__regardless_of_type)
{
   // TODO
}

TEST(Hexagon_System_System,
   submit_current_modal__on_a_ONE_LINE_INPUT_BOX__will_save_the_frontmost_code_editor_stage)
{
   // TODO
}

TEST(Hexagon_System_System,
   set_regex_temp_file_contents_to_word_under_current_advanced_code_editor_cursor__will_do_as_described)
{
   // TODO
}

