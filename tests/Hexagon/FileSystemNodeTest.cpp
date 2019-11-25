
#include <gtest/gtest.h>

#include <Hexagon/FileSystemNode.hpp>

TEST(Hexagon_FileSystemNodeTest, run__returns_the_expected_response)
{
   FileSystemNode program_runner(nullptr);
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, program_runner.run());
}
