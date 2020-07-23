
#include <gtest/gtest.h>

#include <Hexagon/ProjectFactory.hpp>

TEST(Hexagon_ProjectFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::ProjectFactory project_factory;
}

TEST(Hexagon_ProjectFactoryTest, run__returns_the_expected_response)
{
   Hexagon::ProjectFactory project_factory;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, project_factory.run());
}
