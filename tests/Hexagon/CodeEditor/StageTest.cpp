
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

TEST(Hexagon_CodeEditor_StageTest, file_category__has_a_getter_and_has_the_expected_default)
{
   CodeEditor::Stage stage("foobar_filename.txt");
   std::string expected_default_file_category = "undefined";
   std::string actual_default_file_category = stage.get_file_category();
   ASSERT_EQ(expected_default_file_category, actual_default_file_category);
}

TEST(Hexagon_CodeEditor_StageTest,
   infer_cursor_is_on_line_that_exists__returns_true_when_the_cursor_is_within_the_range_of_number_of_lines)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   stage.set_cursor_y(9);
   EXPECT_TRUE(stage.infer_cursor_is_on_line_that_exists());

   stage.set_cursor_y(stage.num_lines()-1);
   EXPECT_TRUE(stage.infer_cursor_is_on_line_that_exists());

   stage.set_cursor_y(0);
   EXPECT_TRUE(stage.infer_cursor_is_on_line_that_exists());
}

TEST(Hexagon_CodeEditor_StageTest,
   infer_cursor_is_on_line_that_exists__returns_false_when_the_cursor_is_not_within_the_range_of_number_of_lines)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   stage.set_cursor_y(-1);
   EXPECT_FALSE(stage.infer_cursor_is_on_line_that_exists());

   stage.set_cursor_y(stage.num_lines());
   EXPECT_FALSE(stage.infer_cursor_is_on_line_that_exists());
}

TEST(Hexagon_CodeEditor_StageTest, join_lines__will_concat_the_contents_of_the_current_line_and_the_line_below_it_and_returns_true)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   stage.set_cursor_y(4);
   ASSERT_EQ(true, stage.join_lines());

   std::string expected_line_at_cursor = "That this huge stage presenteth nought but showsWhereon the stars in secret " \
                                         "influence comment.";

   std::string expected_line_below_cursor = "When I perceive that men as plants increase,";

   ASSERT_EQ(expected_line_at_cursor, stage.current_line_ref());
   ASSERT_EQ(expected_line_below_cursor, stage.next_line_ref());
}

TEST(Hexagon_CodeEditor_StageTest, join_lines__on_the_last_line__does_nothing_and_returns_false)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   stage.set_cursor_y(stage.num_lines()-1);
   EXPECT_EQ("As he takes from you, I engraft you new.", stage.current_line_ref());

   ASSERT_EQ(false, stage.join_lines());

   ASSERT_EQ("As he takes from you, I engraft you new.", stage.current_line_ref());
}

TEST(Hexagon_CodeEditor_StageTest, join_lines__on_a_line_number_that_is_out_of_bounds__does_nothing_and_returns_false)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   int line_numbers_to_test[] = { -1, stage.num_lines()+10, -10, };

   for (auto &line_number_to_test : line_numbers_to_test)
   {
      stage.set_cursor_y(line_number_to_test);
      ASSERT_EQ(false, stage.join_lines());
   }

   SUCCEED();
}

TEST(Hexagon_CodeEditor_StageTest, move_cursor_to_last_line__moves_the_cursor_to_the_last_line_of_the_file)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   ASSERT_EQ(true, stage.move_cursor_to_last_line());
   ASSERT_EQ("As he takes from you, I engraft you new.", stage.current_line_ref());
}

TEST(Hexagon_CodeEditor_StageTest,
   move_cursor_up__when_on_or_above_the_first_line__does_nothing_and_returns_false)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   int line_indices_to_test[] = { 0, -1, -99 };
   for (auto &line_index_to_test : line_indices_to_test)
   {
     stage.set_cursor_y(line_index_to_test);
     ASSERT_EQ(false, stage.move_cursor_up());
   }
}

TEST(Hexagon_CodeEditor_StageTest,
   move_cursor_down__when_on_or_beyond_the_last_line__does_nothing_and_returns_false)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   int last_line_index = stage.num_lines() - 1;

   int line_indices_to_test[] = { last_line_index, last_line_index+1, last_line_index+99};
   for (auto &line_index_to_test : line_indices_to_test)
   {
     stage.set_cursor_y(line_index_to_test);
     ASSERT_EQ(false, stage.move_cursor_down());
   }
}

TEST(Hexagon_CodeEditor_StageTest, delete_line__removes_the_current_line)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   EXPECT_EQ(16, stage.num_lines());

   stage.set_cursor_y(9);

   stage.delete_line();

   EXPECT_EQ(15, stage.num_lines());
   EXPECT_EQ(9, stage.get_cursor_y()); // cursor stays at the same line index

   std::string expected_line_at_cursor = "Then the conceit of this inconstant stay,";

   ASSERT_EQ(expected_line_at_cursor, stage.current_line_ref());

   ASSERT_TRUE(stage.get_content_is_modified());
}

TEST(Hexagon_CodeEditor_StageTest, delete_line__on_an_invalid_line__does_nothing_and_returns_false)
{
   CodeEditor::Stage stage("a_sonnet.txt");
   stage.set_initial_content(SONNET_TEXT);

   stage.set_cursor_y(stage.num_lines()+1);

   EXPECT_EQ(false, stage.delete_line());
   EXPECT_EQ(16, stage.num_lines());
}

TEST(Hexagon_CodeEditor_StageTest,
   move_cursor_to_first_non_whitespace_character__sets_the_cursor_x_to_the_first_non_whitespace_character)
{
   std::vector<std::string> test_text = {
     "   Hello",
     "     \tTest",
     "Start",
   };
   CodeEditor::Stage stage("test_text.txt");
   stage.set_initial_content(test_text);

   ASSERT_EQ(true, stage.move_cursor_to_first_non_whitespace_character());
   ASSERT_EQ(3, stage.get_cursor_x());

   stage.move_cursor_down();

   ASSERT_EQ(true, stage.move_cursor_to_first_non_whitespace_character());
   ASSERT_EQ(6, stage.get_cursor_x());

   stage.move_cursor_down();

   ASSERT_EQ(true, stage.move_cursor_to_first_non_whitespace_character());
   ASSERT_EQ(0, stage.get_cursor_x());
}

