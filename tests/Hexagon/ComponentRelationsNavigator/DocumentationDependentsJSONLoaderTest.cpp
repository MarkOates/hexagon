
#include <gtest/gtest.h>

#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>

TEST(Hexagon_ComponentRelationsNavigator_DocumentationDependentsJSONLoaderTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader documentation_dependents_jsonloader;
}

TEST(Hexagon_ComponentRelationsNavigator_DocumentationDependentsJSONLoaderTest,
   get_DEPENDENTS_JSON_FILENAME__has_the_expected_default)
{
   Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader documentation_dependents_jsonloader;
   std::string expected_string = "/Users/markoates/Repos/hexagon/documentation/dependents.json";

   EXPECT_EQ(expected_string, documentation_dependents_jsonloader.get_DEPENDENTS_JSON_FILENAME());
}

TEST(Hexagon_ComponentRelationsNavigator_DocumentationDependentsJSONLoaderTest,
   build_dependent_names_for_component_name)
{
   Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader documentation_dependents_jsonloader;
   std::vector<std::string> expected_list =
      {
        "Hexagon/AdvancedCodeEditor/Stage",
        "Hexagon/BuildSequenceMeter/Renderer",
        "Hexagon/CodeEditor/Stage",
        "Hexagon/ComponentRelationsNavigator/Stage",
        "Hexagon/Elements/ListMenu",
        "Hexagon/Elements/QuoteRenderer",
        "Hexagon/Elements/StageInfoOverlay",
        "Hexagon/Font",
        "Hexagon/LayoutToStagesCreator",
        "Hexagon/Logo",
        "Hexagon/MissingFile/Stage",
        "Hexagon/StageFactory",
        "Hexagon/TitleScreen",
        "Hexagon/UI/DrawingBox",
        "Hexagon/UI/LittleMenu",
      };

   std::string component_name = "AllegroFlare::FontBin*";
   EXPECT_EQ(expected_list, documentation_dependents_jsonloader.build_dependent_names_for_component_name(component_name));
}

