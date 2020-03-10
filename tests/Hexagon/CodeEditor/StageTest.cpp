
#include <gtest/gtest.h>

#include <Hexagon/CodeEditor/Stage.hpp>

const std::string SONNET_TEXT = R"END(Sonnet 15

When I consider every thing that grows
Holds in perfection but a little moment.
That this huge stage presenteth nought but shows
Whereon the stars in secret influence comment.
When I perceive that men as plants increase,
Cheered and checked even by the self-same sky:
Vaunt in their youthful sap, at height decrease,
And wear their brave state out of memory.
Then the conceit of this inconstant stay,
Sets you most rich in youth before my sight,
Where wasteful time debateth with decay
To change your day of youth to sullied night,
And all in war with Time for love of you,
As he takes from you, I engraft you new.)END";

TEST(Hexagon_CodeEditor_StageTest, can_be_created_without_blowing_up)
{
   CodeEditor::Stage stage("foobar_filename.txt");
}

TEST(Hexagon_CodeEditor_StageTest, delete_line__removes_the_current_line)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   EXPECT_EQ(16, stage.num_lines());

   stage.set_cursor_y(9);

   stage.delete_line();

   EXPECT_EQ(15, stage.num_lines());
   EXPECT_EQ(9, stage.get_cursor_y()); // cursor stays at the same line number

   std::string expected_line_at_cursor = "Then the conceit of this inconstant stay,";

   ASSERT_EQ(expected_line_at_cursor, stage.current_line_ref());

   ASSERT_TRUE(stage.get_content_is_modified());
}

