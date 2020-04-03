
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/System/Action/AttemptToCraeteCodeEditorStageFromFilename.hpp>

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
