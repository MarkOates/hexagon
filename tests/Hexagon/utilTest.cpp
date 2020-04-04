#include <gtest/gtest.h>

#include <Hexagon/util.hpp>

static std::string TEST_FIXTURE_DIRECTORY_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";
static std::string NONEXISTENT_TEST_FIXTURE_FILE = TEST_FIXTURE_DIRECTORY_ROOT + "file_that_does_not_exist.txt";
static std::string TEST_FIXTURE_TEXT_FILE = TEST_FIXTURE_DIRECTORY_ROOT + "file_that_contains_several_lines.txt";

#include <Blast/FileExistenceChecker.hpp>

TEST(Hexagon_util, expected_test_fixtures_are_in_place)
{
   ASSERT_EQ(false, Blast::FileExistenceChecker(NONEXISTENT_TEST_FIXTURE_FILE).exists());
   ASSERT_EQ(true, Blast::FileExistenceChecker(TEST_FIXTURE_TEXT_FILE).exists());
}

TEST(Hexagon_util, read_file__with_a_valid_file__reads_the_contents_into_the_lines_and_returns_true)
{
   std::vector<std::string> lines;

   ASSERT_EQ(true, ::read_file(lines, TEST_FIXTURE_TEXT_FILE));

   std::vector<std::string> expected_lines = {
      "Sonnet 40",
      "",
      "Take all my loves, my love, yea take them all,",
      "What hast thou then more than thou hadst before?",
      "No love, my love, that thou mayst true love call,",
      "All mine was thine, before thou hadst this more:",
      "Then if for my love, thou my love receivest,",
      "I cannot blame thee, for my love thou usest,",
      "But yet be blamed, if thou thy self deceivest",
      "By wilful taste of what thy self refusest.",
      "I do forgive thy robbery gentle thief",
      "Although thou steal thee all my poverty:",
      "And yet love knows it is a greater grief",
      "To bear greater wrong, than hate's known injury.",
      "Lascivious grace, in whom all ill well shows,",
      "Kill me with spites yet we must not be foes.",
   };

   ASSERT_EQ(expected_lines, lines);
}

TEST(Hexagon_util, read_file__with_a_file_that_does_not_exist__returns_false)
{
   std::vector<std::string> lines;

   ASSERT_EQ(false, ::read_file(lines, NONEXISTENT_TEST_FIXTURE_FILE));
}

TEST(Hexagon_util, read_file__with_a_file_that_does_not_exist__does_not_create_the_file)
{
   std::vector<std::string> lines;

   EXPECT_EQ(false, ::read_file(lines, NONEXISTENT_TEST_FIXTURE_FILE));

   ASSERT_EQ(false, Blast::FileExistenceChecker(NONEXISTENT_TEST_FIXTURE_FILE).exists());
}

TEST(Hexagon_util, read_file__with_a_file_that_does_not_exist__clears_the_lines)
{
   std::vector<std::string> lines = {
      "A mountain village",
      "under the piled-up snow",
      "the sound of water.",
   };

   EXPECT_EQ(false, ::read_file(lines, NONEXISTENT_TEST_FIXTURE_FILE));

   ASSERT_EQ(true, lines.empty());
}

