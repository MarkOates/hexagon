
#include <gtest/gtest.h>

#include <Hexagon/BuildSystem/BuildFactory.hpp>


TEST(Hexagon_BuildSystem_BuildFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::BuildSystem::BuildFactory build_factory;
}


TEST(Hexagon_BuildSystem_BuildFactoryTest, run__returns_the_expected_response)
{
   Hexagon::BuildSystem::BuildFactory build_factory;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, build_factory.run());
}

