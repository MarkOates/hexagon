
#include <gtest/gtest.h>

#include <Hexagon/FilesOpenedHistory.hpp>

TEST(Hexagon_FilesOpenedHistoryTest, files_contains_the_list_of_recently_opened_files)
{
   Hexagon::FilesOpenedHistory files_opened_history;

   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, files_opened_history.run());
}
