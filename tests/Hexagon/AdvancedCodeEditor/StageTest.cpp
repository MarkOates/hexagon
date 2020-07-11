
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/Stage.hpp>

TEST(Hexagon_AdvancedCodeEditor_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
}

TEST(Hexagon_AdvancedCodeEditor_StageTest, run__returns_the_expected_response)
{
   Hexagon::AdvancedCodeEditor::Stage stage;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, stage.run());
}
