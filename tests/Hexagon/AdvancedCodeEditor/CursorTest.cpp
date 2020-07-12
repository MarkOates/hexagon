
#include <gtest/gtest.h>

#include <Hexagon/AdvancedCodeEditor/Cursor.hpp>

TEST(Hexagon_AdvancedCodeEditor_CursorTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedCodeEditor::Cursor cursor;
}

TEST(Hexagon_AdvancedCodeEditor_CursorTest, move_up__decrements_the_y_position)
{
   Hexagon::AdvancedCodeEditor::Cursor cursor;
   cursor.move_up();
   ASSERT_EQ(-1, cursor.get_y());
}

TEST(Hexagon_AdvancedCodeEditor_CursorTest, move_down__decrements_the_y_position)
{
   Hexagon::AdvancedCodeEditor::Cursor cursor;
   cursor.move_down();
   ASSERT_EQ(1, cursor.get_y());
}

TEST(Hexagon_AdvancedCodeEditor_CursorTest, move_left__decrements_the_y_position)
{
   Hexagon::AdvancedCodeEditor::Cursor cursor;
   cursor.move_left();
   ASSERT_EQ(-1, cursor.get_x());
}

TEST(Hexagon_AdvancedCodeEditor_CursorTest, move_right__decrements_the_y_position)
{
   Hexagon::AdvancedCodeEditor::Cursor cursor;
   cursor.move_right();
   ASSERT_EQ(1, cursor.get_x());
}

