
#include <gtest/gtest.h>

#include <Hexagon/LayoutFromYAML.hpp>

std::string YAML_SOURCE_FIXTURE = R"END(
name: Component/NameFromFixture
files:
  - filename: quintessence/Component/NameFromFixture.q.yml
    file_type: quintessence
    placement: 0
daemus_command: 'echo "hello"'
)END";

std::string YAML_SOURCE_FIXTURE_WITH_MULTIPLE_FILES = R"END(
name: Component/NameFromFixture
files:
  - filename: quintessence/Component/NameFromFixture.q.yml
    file_type: quintessence
    placement: 0
  - filename: tests/Component/NameFromFixtureTest.cpp
    file_type: cpp_test
    placement: 0
daemus_command: 'echo "hello"'
)END";

TEST(Hexagon__LayoutFromYAMLTest, can_be_created_without_blowing_up)
{
   Hexagon::LayoutFromYAML layout_from_yaml;
}

TEST(Hexagon__LayoutFromYAMLTest, DISABLED__load__by_defaut_returns_an_empty_layout)
{
   Hexagon::LayoutFromYAML layout_from_yaml;
   Hexagon::Layout expected_layout;
   Hexagon::Layout actual_layout = layout_from_yaml.load();

   EXPECT_EQ(expected_layout.get_concept_name(), actual_layout.get_concept_name());
   EXPECT_EQ(expected_layout.get_files().empty(), actual_layout.get_files().empty());
   EXPECT_EQ(expected_layout.get_daemus_command().empty(), actual_layout.get_daemus_command().empty());
}

TEST(Hexagon__LayoutFromYAMLTest, load__parses_the_concept_name)
{
   std::string yaml_source = "name: AnExpected/ConceptName";
   Hexagon::LayoutFromYAML layout_from_yaml(yaml_source);
   Hexagon::Layout expected_layout("AnExpected/ConceptName");

   Hexagon::Layout actual_layout = layout_from_yaml.load();

   EXPECT_EQ(expected_layout.get_concept_name(), actual_layout.get_concept_name());
}

TEST(Hexagon__LayoutFromYAMLTest, load__parses_the_files)
{
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE);

   Hexagon::Layout layout = layout_from_yaml.load();

   std::vector<std::tuple<std::string, std::string, placement3d>> expected_files = {
      {
         "quintessence/Component/NameFromFixture.q.yml",
         "quintessence",
         placement3d{ 0 },
      },
   };
   std::vector<std::tuple<std::string, std::string, placement3d>> actual_files = layout.get_files();

   EXPECT_EQ(expected_files, actual_files);
}

TEST(Hexagon__LayoutFromYAMLTest, load__parses_multiple_files)
{
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE_WITH_MULTIPLE_FILES);

   Hexagon::Layout layout = layout_from_yaml.load();

   std::vector<std::tuple<std::string, std::string, placement3d>> expected_files = {
      {
         "quintessence/Component/NameFromFixture.q.yml",
         "quintessence",
         placement3d{ 0 },
      },
      {
         "tests/Component/NameFromFixtureTest.cpp",
         "cpp_test",
         placement3d{ 0 },
      },
   };
   std::vector<std::tuple<std::string, std::string, placement3d>> actual_files = layout.get_files();

   EXPECT_EQ(expected_files, actual_files);
}

TEST(Hexagon__LayoutFromYAMLTest, load__parses_the_daemus_command)
{
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE);

   Hexagon::Layout actual_layout = layout_from_yaml.load();

   std::string expected_daemus_command = "echo \"hello\"";
   std::string actual_daemus_command = actual_layout.get_daemus_command();

   EXPECT_EQ(expected_daemus_command, actual_daemus_command);
}

TEST(Hexagon__LayoutFromYAMLTest, load__without_a_damus_command_sets_to_empty_string)
{
   // TODO
}

TEST(Hexagon__LayoutFromYAMLTest, DISABLED_load__parses_the_placement)
{
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE);

   Hexagon::Layout layout = layout_from_yaml.load();

   //placement3d expected_placement = placement3d{ 7.0, 23.6, 1.34 };
   placement3d expected_placement = placement3d{};
   placement3d actual_placement = placement3d{};

   EXPECT_EQ(expected_placement, actual_placement);
}

