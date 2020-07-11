
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>

TEST(Hexagon_AdvancedCodeEditor_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
}

TEST(Hexagon_AdvancedCodeEditor_StageTest, render__when_allegro_is_not_initialized__raises_an_error)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.render(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_AdvancedCodeEditor_StageTest, process_local_event__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   stage.process_local_event();
   SUCCEED();
}

TEST(Hexagon_AdvancedCodeEditor_StageTest, process_event__does_not_blow_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   stage.process_event();
   SUCCEED();
}

TEST(Hexagon_AdvancedCodeEditor_StageTest, render__renders_the_advanced_code_editor)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1280 * 2, 720 * 2);

   Hexagon::AdvancedCodeEditor::Stage stage;

   stage.render();

   al_flip_display();

   sleep(1);

   al_destroy_display(display);
   al_uninstall_system();
}

