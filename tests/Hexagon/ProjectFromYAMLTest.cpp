
#include <gtest/gtest.h>

#include <Hexagon/ProjectFromYAML.hpp>

TEST(Hexagon_ProjectFromYAMLTest, can_be_created_without_blowing_up)
{
   Hexagon::ProjectFromYAML project_from_yaml;
}

TEST(Hexagon_ProjectFromYAMLTest, load__returns_the_expected_response)
{
   Hexagon::ProjectFromYAML project_from_yaml;
   project_from_yaml.load();
   SUCCEED();
}

