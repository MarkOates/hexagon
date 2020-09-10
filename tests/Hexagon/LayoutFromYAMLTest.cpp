
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/LayoutFromYAML.hpp>
#include <yaml-cpp/yaml.h>

std::string YAML_SOURCE_FIXTURE = R"END(
name: Component/NameFromFixture
files:
  - filename: quintessence/Component/NameFromFixture.q.yml
    file_type: quintessence
daemus_command: 'echo "hello"'
)END";

std::string YAML_SOURCE_FIXTURE_WITHOUT_DAEMUS_COMMAND = R"END(
name: Component/NameFromFixture
files:
  - filename: quintessence/Component/NameFromFixture.q.yml
    file_type: quintessence
)END";

std::string YAML_SOURCE_FIXTURE_WITHOUT_CONCEPT_NAME = R"END(
files:
  - filename: quintessence/Component/NameFromFixture.q.yml
    file_type: quintessence
)END";

std::string YAML_SOURCE_FIXTURE_WITH_MULTIPLE_FILES = R"END(
name: Component/NameFromFixture
files:
  - filename: quintessence/Component/NameFromFixture.q.yml
    file_type: quintessence
  - filename: tests/Component/NameFromFixtureTest.cpp
    file_type: cpp_test
daemus_command: 'echo "hello"'
)END";

std::string YAML_SOURCE_FIXTURE_WITH_PLACEMENT = R"END(
name: Component/NameFromFixture
files:
  - filename: quintessence/Component/NameFromFixture.q.yml
    file_type: quintessence
    placement:
      x: 7.0
      y: 23.6
      z: 1.34
daemus_command: 'echo "hello"'
)END";

TEST(Hexagon__LayoutFromYAMLTest, can_be_created_without_blowing_up)
{
   Hexagon::LayoutFromYAML layout_from_yaml;
}

TEST(Hexagon__LayoutFromYAMLTest, load__by_defaut_returns_an_empty_layout)
{
   Hexagon::LayoutFromYAML layout_from_yaml;
   Hexagon::Layout expected_layout("");
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
   YAML::Node node = YAML::Load(YAML_SOURCE_FIXTURE);
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
   YAML::Node node = YAML::Load(YAML_SOURCE_FIXTURE_WITH_MULTIPLE_FILES);
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
   YAML::Node node = YAML::Load(YAML_SOURCE_FIXTURE);
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE);

   Hexagon::Layout actual_layout = layout_from_yaml.load();

   std::string expected_daemus_command = "echo \"hello\"";
   std::string actual_daemus_command = actual_layout.get_daemus_command();

   EXPECT_EQ(expected_daemus_command, actual_daemus_command);
}

TEST(Hexagon__LayoutFromYAMLTest, load__without_a_daemus_command__sets_to_an_empty_string)
{
   YAML::Node node = YAML::Load(YAML_SOURCE_FIXTURE_WITHOUT_DAEMUS_COMMAND);
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE_WITHOUT_DAEMUS_COMMAND);

   Hexagon::Layout actual_layout = layout_from_yaml.load();

   std::string expected_daemus_command = "";
   std::string actual_daemus_command = actual_layout.get_daemus_command();

   EXPECT_EQ(expected_daemus_command, actual_daemus_command);
}

TEST(Hexagon__LayoutFromYAMLTest, load__without_a_concept_name__sets_to_an_empty_string)
{
   YAML::Node node = YAML::Load(YAML_SOURCE_FIXTURE_WITHOUT_CONCEPT_NAME);
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE_WITHOUT_CONCEPT_NAME);

   Hexagon::Layout actual_layout = layout_from_yaml.load();

   std::string expected_daemus_command = "";
   std::string actual_daemus_command = actual_layout.get_daemus_command();

   EXPECT_EQ(expected_daemus_command, actual_daemus_command);
}

TEST(Hexagon__LayoutFromYAMLTest, load__without_a_damus_command_sets_to_empty_string)
{
   // TODO
}

TEST(Hexagon__LayoutFromYAMLTest, load__parses_the_file_placements)
{
   YAML::Node node = YAML::Load(YAML_SOURCE_FIXTURE_WITH_PLACEMENT);
   Hexagon::LayoutFromYAML layout_from_yaml(YAML_SOURCE_FIXTURE_WITH_PLACEMENT);
   placement3d placement = placement3d{ 7.0, 23.6, 1.34 };

   Hexagon::Layout layout = layout_from_yaml.load();

   placement3d expected_placement = placement;
   placement3d actual_placement = std::get<2>(layout.get_files()[0]);

   EXPECT_EQ(expected_placement, actual_placement);
}

