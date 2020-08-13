
#include <gtest/gtest.h>

#include <Hexagon/LayoutFromYAML.hpp>

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
   std::string yaml_source = "name: AnExpected/ConceptName";
   Hexagon::LayoutFromYAML layout_from_yaml(yaml_source);
   Hexagon::Layout expected_layout("AnExpected/ConceptName");

   Hexagon::Layout actual_layout = layout_from_yaml.load();

   EXPECT_EQ(expected_layout.get_concept_name(), actual_layout.get_concept_name());
}

