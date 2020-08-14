
#include <gtest/gtest.h>

#include <Hexagon/ProjectFromYAML.hpp>

std::string FULL_TEST_FIXTURE = R"END(
project_name:
)END";

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

TEST(Hexagon_ProjectFromYAMLTest, load__returns_a_project_with_the_expected_values)
{
   Hexagon::ProjectFromYAML project_from_yaml(FULL_TEST_FIXTURE);

   Hexagon::Project expected_project;
   Hexagon::Project actual_project = project_from_yaml.load();

   ASSERT_EQ(expected_project.get_project_name(), actual_project.get_project_name());
}

TEST(Hexagon_ProjectFromYAMLTest, load__returns_a_project_with_the_expected_values_for_layouts)
{
   Hexagon::ProjectFromYAML project_from_yaml(FULL_TEST_FIXTURE);

   std::vector<std::tuple<std::string, Hexagon::Layout>> expected_layouts;
   Hexagon::Project expected_project;
   Hexagon::Project actual_project = project_from_yaml.load();

   ASSERT_EQ(expected_project.get_project_name(), actual_project.get_project_name());
}

