
#include <gtest/gtest.h>

#include <Hexagon/System/Action/AttemptToCraeteCodeEditorStageFromFilename.hpp>

TEST(Hexagon_System_Action_AttemptToCraeteCodeEditorStageFromFilenameTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename attempt_to_craete_code_editor_stage_from_filename;
}

TEST(Hexagon_System_Action_AttemptToCraeteCodeEditorStageFromFilenameTest, run__returns_the_expected_response)
{
   Hexagon::System::Action::AttemptToCraeteCodeEditorStageFromFilename attempt_to_craete_code_editor_stage_from_filename;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, attempt_to_craete_code_editor_stage_from_filename.run());
}
