#include <gtest/gtest.h>

#include <Hexagon/util.hpp>

static std::string TEST_FIXTURE_DIRECTORY_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";
static std::string NONEXISTENT_TEST_FIXTURE_FILE = TEST_FIXTURE_DIRECTORY_ROOT + "file_that_does_not_exist.txt";

#include <Blast/FileExistenceChecker.hpp>

TEST(Hexagon_util, expected_test_fixtures_are_in_place)
{
   ASSERT_EQ(false, Blast::FileExistenceChecker(NONEXISTENT_TEST_FIXTURE_FILE).exists());
}

TEST(Hexagon_util_, read_file__with_a_file_that_does_not_exist__does_not_create_the_file)
{
   std::vector<std::string> lines;

   ::read_file(lines, NONEXISTENT_TEST_FIXTURE_FILE);

   ASSERT_EQ(false, Blast::FileExistenceChecker(NONEXISTENT_TEST_FIXTURE_FILE).exists());
}

