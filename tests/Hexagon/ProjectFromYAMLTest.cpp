
#include <gtest/gtest.h>

#include <Hexagon/ProjectFromYAML.hpp>

std::string FULL_TEST_FIXTURE = R"END(
components:


  - name: Component/NameFromFixture
    files:
      - filename: quintessence/Component/NameFromFixture.q.yml
        file_type: quintessence
        placement:
          x: 7.0
          y: 23.6
          z: 1.34
      - filename: tests/Component/NameFromFixtureTest.cpp
        file_type: cpp_test
        placement:
          x: 100.0
          y: 23.6
          z: 1.34
    daemus:
      - command: 'echo "hello"'


  - name: Component/Something/AnotherComponent
    files:
      - filename: quintessence/Component/Something/AnotherComponent.q.yml
        file_type: quintessence
        placement:
          x: 7.0
          y: 23.6
          z: 1.34
      - filename: tests/Component/Something/AnotherComponentTest.cpp
        file_type: cpp_test
        placement:
          x: 100.0
          y: 23.6
          z: 1.34
    daemus:
      - command: 'echo "hello"'


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

TEST(Hexagon_ProjectFromYAMLTest, load__returns_a_project_with_the_expected_name)
{
   std::string project_name = "FoobarProject";
   Hexagon::ProjectFromYAML project_from_yaml(project_name, FULL_TEST_FIXTURE);
   Hexagon::Project project = project_from_yaml.load();

   std::string expected_project_name = project_name;
   std::string actual_project_name = project.get_project_name();

   ASSERT_EQ(expected_project_name, actual_project_name);
}

TEST(Hexagon_ProjectFromYAMLTest, load__returns_a_project_with_the_expected_values_for_layouts)
{
   Hexagon::ProjectFromYAML project_from_yaml("UnnamedProject", FULL_TEST_FIXTURE);
   Hexagon::Project project = project_from_yaml.load();

   std::vector<std::tuple<std::string, Hexagon::Layout>> expected_layouts = {
      { "Component/NameFromFixture", Hexagon::Layout() },
      { "Component/Something/AnotherComponent", Hexagon::Layout() },
   };
   std::vector<std::tuple<std::string, Hexagon::Layout>> actual_layouts = project.get_layouts();

   ASSERT_EQ(2, actual_layouts.size());
   ASSERT_EQ(2, expected_layouts.size());

   EXPECT_EQ(std::get<0>(expected_layouts[0]), std::get<0>(actual_layouts[0]));
   EXPECT_EQ(std::get<0>(expected_layouts[0]), std::get<1>(actual_layouts[0]).get_concept_name());
   // TODO: assert on the layout... or not?  It's already comprehensively tested in LayoutFromYAML

   EXPECT_EQ(std::get<0>(expected_layouts[1]), std::get<0>(actual_layouts[1]));
   EXPECT_EQ(std::get<0>(expected_layouts[1]), std::get<1>(actual_layouts[1]).get_concept_name());
   // TODO: assert on the layout... or not?  It's already comprehensively tested in LayoutFromYAML
}

