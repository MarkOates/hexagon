
#include <gtest/gtest.h>

#include <Hexagon/ProjectFromYAML.hpp>

//bool operator==(const Hexagon::Project &project_a, const Hexagon::Project &project_b)
//{
//   return true;
//}


std::string FULL_TEST_FIXTURE = R"END(
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

   //ASSERT_EQ(expected_project, actual_project);
}

