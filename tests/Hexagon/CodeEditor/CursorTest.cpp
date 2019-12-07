
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Cursor.hpp>

TEST(Hexagon_CodeEditor_CursorTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeEditor::Cursor cursor;
}

TEST(Hexagon_CodeEditor_CursorTest, run__returns_the_expected_response)
{
   Hexagon::CodeEditor::Cursor cursor;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, cursor.run());
}
