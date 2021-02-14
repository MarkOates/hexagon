
#include <gtest/gtest.h>

#include <Hexagon/GitCommitMessageInputBox/Stage.hpp>

TEST(Hexagon_GitCommitMessageInputBox_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::GitCommitMessageInputBox::Stage stage;
}

TEST(Hexagon_GitCommitMessageInputBox_StageTest,
   code_editor_char_count__when_empty__returns_the_expected_number_of_characers)
{
   Hexagon::GitCommitMessageInputBox::Stage stage;
   ASSERT_EQ(0, stage.code_editor_char_count());
}

TEST(Hexagon_GitCommitMessageInputBox_StageTest,
   code_editor_char_count__with_empty_line__returns_the_expected_character_count)
{
   Hexagon::GitCommitMessageInputBox::Stage stage;
   stage.get_code_editor_ref().set_initial_content("");
   ASSERT_EQ(0, stage.code_editor_char_count());
}

TEST(Hexagon_GitCommitMessageInputBox_StageTest,
   code_editor_char_count__with_empty_lines__includes_newlines_in_character_count)
{
   Hexagon::GitCommitMessageInputBox::Stage stage;
   stage.get_code_editor_ref().set_initial_content(std::vector<std::string>({ "", "", "" }));
   ASSERT_EQ(2, stage.code_editor_char_count());
}

TEST(Hexagon_GitCommitMessageInputBox_StageTest, code_editor_char_count__returns_the_expected_char_count)
{
   Hexagon::GitCommitMessageInputBox::Stage stage;
   stage.get_code_editor_ref().set_initial_content("Hello, char count!");
   ASSERT_EQ(18, stage.code_editor_char_count());
}

TEST(Hexagon_GitCommitMessageInputBox_StageTest, code_editor_char_count__returns_the_expected_char_count_2)
{
   Hexagon::GitCommitMessageInputBox::Stage stage;
   stage.get_code_editor_ref().set_initial_content(
      std::vector<std::string>({
         "Hello, char count!",
         "You have",
         "multiple lines",
      })
   );
   ASSERT_EQ(42, stage.code_editor_char_count());
}

