
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

static std::string TEST_FIXTURE_DIRECTORY_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";
static std::string TEST_FIXTURE_TEXT_FILE = TEST_FIXTURE_DIRECTORY_ROOT + "file_that_contains_several_lines.txt";

#include <Hexagon/System/Action/AttemptToCraeteCodeEditorStageFromFilename.hpp>

#include <Blast/FileExistenceChecker.hpp>

TEST(Hexagon_System_Action_AttemptToCraeteCodeEditorStageFromFilenameTest, test_fixture_files_exist)
{
   ASSERT_EQ(true, Blast::FileExistenceChecker(TEST_FIXTURE_TEXT_FILE).exists());
}

TEST(Hexagon_System_Action_AttemptToCraeteCodeEditorStageFromFilenameTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename attempt_to_craete_code_editor_stage_from_filename;
}

TEST(Hexagon_System_Action_AttemptToCraeteCodeEditorStageFromFilenameTest, execute__with_nullptr_stages__throws_an_error)
{
   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action;
   std::string expected_error_message = "[Hexagon/System/Action/AttemptToCreateCodeEditorStageFromFilename error:] " \
                                        "cannot \"execute\" with nullptr stages";
   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_Action_AttemptToCraeteCodeEditorStageFromFilenameTest,
   execute__on_a_file_that_does_not_exist__throws_an_error)
{
   std::vector<StageInterface *> stages = {};
   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action(
      "file_that_does_not_exist.txt",
      300,
      200,
      100,
      &stages);

   std::string expected_error_message = "Could not open the selected file";
   ASSERT_THROW_WITH_MESSAGE(action.execute(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_System_Action_AttemptToCraeteCodeEditorStageFromFilenameTest,
   execute__adds_a_new_code_editor_stage_to_stages)
{
   std::vector<StageInterface *> stages = {};
   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename action(
      TEST_FIXTURE_TEXT_FILE,
      300,
      200,
      100,
      &stages);

   EXPECT_EQ(true, action.execute());
   EXPECT_EQ(1, stages.size());

   StageInterface *created_stage = stages.back();
   StageInterface::type_t expected_stage_type = StageInterface::type_t::CODE_EDITOR;
   StageInterface::type_t actual_stage_type = created_stage->get_type();

   EXPECT_EQ(expected_stage_type, actual_stage_type);
}

