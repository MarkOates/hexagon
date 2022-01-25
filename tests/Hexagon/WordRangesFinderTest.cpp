
#include <gtest/gtest.h>

#include <Hexagon/WordRangesFinder.hpp>

TEST(Hexagon_WordRangesFinderTest, can_be_created_without_blowing_up)
{
   Hexagon::WordRangesFinder word_ranges_finder;
}

TEST(Hexagon_WordRangesFinderTest,
   find_ranges__with_cursor_before_the_first_character_in_the_line__returns_a_pair_with_a_negative_one_first_element)
{
   Hexagon::WordRangesFinder word_ranges_finder("This is the line of text for testing", -1);
   std::pair<int, int> expected_ranges_result = std::pair<int, int>(-1, -1);
   std::pair<int, int> actual_ranges_result = word_ranges_finder.find_ranges();
   EXPECT_EQ(expected_ranges_result, actual_ranges_result);
}

TEST(Hexagon_WordRangesFinderTest,
   find_ranges__with_cursor_beyond_the_first_character_in_the_line__returns_a_pair_with_a_negative_one_first_element)
{
   Hexagon::WordRangesFinder word_ranges_finder("This is the line of text for testing", 999);
   std::pair<int, int> expected_ranges_result = std::pair<int, int>(-1, -1);
   std::pair<int, int> actual_ranges_result = word_ranges_finder.find_ranges();
   EXPECT_EQ(expected_ranges_result, actual_ranges_result);
}

TEST(Hexagon_WordRangesFinderTest,
   find_ranges__will_return_the_position_and_length_of_a_full_word_underneath_the_cursor_pos)
{
   Hexagon::WordRangesFinder word_ranges_finder("This is the line of text for testing", 13);
                                  // cursor_pos (13) is here  ^
   std::pair<int, int> expected_ranges_result = std::pair<int, int>(12, 4);
   std::pair<int, int> actual_ranges_result = word_ranges_finder.find_ranges();
   EXPECT_EQ(expected_ranges_result, actual_ranges_result);
}

TEST(Hexagon_WordRangesFinderTest, find_ranges__when_the_cursor_is_on_a_non_word_character__returns_a_nofind_result)
{
   Hexagon::WordRangesFinder word_ranges_finder("This is the l:ne of text for testing", 13);
                                  // cursor_pos (13) is here  ^
   std::pair<int, int> expected_ranges_result = std::pair<int, int>(-1, -1);
   std::pair<int, int> actual_ranges_result = word_ranges_finder.find_ranges();
   EXPECT_EQ(expected_ranges_result, actual_ranges_result);
}

TEST(Hexagon_WordRangesFinderTest, is_valid__returns_false_if_the_pair_is_not_a_valid_range)
{
   // TODO
}

TEST(Hexagon_WordRangesFinderTest, is_valid__returns_true_if_the_pair_is_a_valid_range)
{
   // TODO
}
