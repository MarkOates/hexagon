
#include <gtest/gtest.h>

#include <Hexagon/Daemus/BuildFactory.hpp>

TEST(Hexagon_Daemus_BuildFactoryTest, can_be_created_without_blowing_up)
{
   Hexagon::Daemus::BuildFactory build_factory;
}

TEST(Hexagon_Daemus_BuildFactoryTest, run__returns_the_expected_response)
{
   Hexagon::Daemus::BuildFactory build_factory;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, build_factory.run());
}
