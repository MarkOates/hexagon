
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

static std::string TEST_FIXTURE_DIRECTORY_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";
static std::string TEST_FIXTURE_TEXT_FILE = TEST_FIXTURE_DIRECTORY_ROOT + "file_that_contains_several_lines.txt";

#include <Hexagon/System/Action/AttemptToCreateCodeEditorStageFromFilename.hpp>

class Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithStageFactoryFixture.hpp>

class Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithFixture
   : public Testing::WithStageFactoryFixture
{};

#include <Blast/FileExistenceChecker.hpp>

TEST_F(Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithEmptyFixture,
   test_fixture_files_exist)
{
   ASSERT_EQ(true, Blast::FileExistenceChecker(TEST_FIXTURE_TEXT_FILE).exists());
}

TEST_F(Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::System::Action::AttemptToCreateCodeEditorStageFromFilename attempt_to_craete_code_editor_stage_from_filename;
}

TEST_F(Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithEmptyFixture,
   execute__with_nullptr_stages__throws_an_error)
{
   Hexagon::System::Action::AttemptToCreateCodeEditorStageFromFilename action;
   std::string expected_error_message = "AttemptToCreateCodeEditorStageFromFilename::execute: error: " \
                                        "guard \"stages\" not met";
   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithEmptyFixture,
   execute__with_nullptr_stage_factory__throws_an_error)
{
   std::vector<StageInterface *> stages = {};
   Hexagon::System::Action::AttemptToCreateCodeEditorStageFromFilename action(
      TEST_FIXTURE_TEXT_FILE,
      300,
      200,
      100,
      130,
      ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f},
      ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f},
      &stages,
      nullptr
   );
   std::string expected_error_message = "AttemptToCreateCodeEditorStageFromFilename::execute: error: " \
                                        "guard \"stage_factory\" not met";
   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithFixture,
   execute__on_a_file_that_does_not_exist__throws_an_error)
{
   std::vector<StageInterface *> stages = {};
   Hexagon::System::Action::AttemptToCreateCodeEditorStageFromFilename action(
      "file_that_does_not_exist.txt",
      300,
      200,
      100,
      130,
      ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f},
      ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f},
      &stages,
      &get_stage_factory_ref()
   );

   std::string expected_error_message = "Could not open the selected file";
   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_System_Action_AttemptToCreateCodeEditorStageFromFilenameTestWithFixture,
   execute__adds_a_new_code_editor_stage_to_stages)
{
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
   std::vector<StageInterface *> stages = {};
   Hexagon::System::Action::AttemptToCreateCodeEditorStageFromFilename action(
      TEST_FIXTURE_TEXT_FILE,
      300,
      200,
      100,
      130,
      ALLEGRO_COLOR{1.0f, 1.0f, 1.0f, 1.0f},
      ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f},
      &stages,
      &get_stage_factory_ref()
   );

   EXPECT_EQ(true, action.execute());
   EXPECT_EQ(1, stages.size());

   StageInterface *created_stage = stages.back();
   StageInterface::type_t expected_stage_type = StageInterface::type_t::CODE_EDITOR;
   StageInterface::type_t actual_stage_type = created_stage->get_type();

   EXPECT_EQ(expected_stage_type, actual_stage_type);
   al_destroy_display(display);
}

