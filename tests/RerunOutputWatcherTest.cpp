
#include <gtest/gtest.h>

#include <RerunOutputWatcher.hpp>

TEST(RerunOutputWatcherTest, run__returns_the_expected_response)
{
   RerunOutputWatcher program_runner;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, program_runner.run());
}
