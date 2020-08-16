
#include <gtest/gtest.h>

#include <Hexagon/CodeMessagePointManager.hpp>

TEST(Hexagon_CodeMessagePointManagerTest, can_be_created_without_blowing_up)
{
   Hexagon::CodeMessagePointManager code_message_point_manager;
}

TEST(Hexagon_CodeMessagePointManagerTest, run__returns_the_expected_response)
{
   Hexagon::CodeMessagePointManager code_message_point_manager;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, code_message_point_manager.run());
}
