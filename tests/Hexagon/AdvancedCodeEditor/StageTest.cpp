
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

static std::string FIXTURE_PASSAGE = R"PASSAGE(       - 64 -
Act without doing;
work without effort.
Think of the small as large
and the few as many.
Confront the difficult
while it is still easy;
accomplish the great task
by a series of small acts.

The Master never reaches for the great;
thus she achieves greatness.
When she runs into a difficulty,
she stops and gives herself to it.
She doesn't cling to her own comfort;
thus problems are no problem for her.
)PASSAGE";

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

TEST(Hexagon_AdvancedCodeEditor_StageTest, initialize__without_a_fon_bin__raises_an_error)
{
   al_init();

   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::initialize: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.initialize(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}

TEST(Hexagon_AdvancedCodeEditor_StageTest, render__if_not_initialized__raises_an_error)
{
   al_init();

   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_error_message = "Stage::render: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage.render(), std::runtime_error, expected_error_message);

   al_uninstall_system();
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

TEST(Hexagon_AdvancedCodeEditor_StageTest, set_initial_content__fills_the_text_mesh_with_the_expected_content)
{
}

TEST(Hexagon_AdvancedCodeEditor_StageTest, render__renders_the_advanced_code_editor)
{
   al_init();
   al_init_font_addon();
   al_init_ttf_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1280 * 2, 720 * 2);
   AllegroFlare::FontBin font_bin;
   font_bin.set_full_path("/Users/markoates/Repos/hexagon/bin/programs/data/fonts");

   Hexagon::AdvancedCodeEditor::Stage stage(&font_bin, 40, 30);
   stage.initialize();

   stage.set_initial_content(FIXTURE_PASSAGE);

   stage.render();

   al_flip_display();

   sleep(1);

   font_bin.clear();
   al_destroy_display(display);
   al_uninstall_system();
}

