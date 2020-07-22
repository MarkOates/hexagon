
#include <gtest/gtest.h>

#include <Hexagon/Project.hpp>

TEST(Hexagon_ProjectTest, can_be_created_without_blowing_up)
{
   Hexagon::Project project;
}

TEST(Hexagon_ProjectTest, run__returns_the_expected_response)
{
   Hexagon::Project project;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, project.run());
}
