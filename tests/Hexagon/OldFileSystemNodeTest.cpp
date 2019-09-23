
#include <gtest/gtest.h>

#include <Hexagon/OldFileSystemNode.hpp>

TEST(Hexagon_OldFileSystemNodeTest, run__returns_the_expected_response)
{
   OldFileSystemNode program_runner(nullptr);
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}
