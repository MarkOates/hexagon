
#include <gtest/gtest.h>

#include <Hexagon/FilesOpenedHistory.hpp>

TEST(Hexagon_FilesOpenedHistoryTest, run__returns_the_expected_response)
{
   Hexagon::FilesOpenedHistory program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
