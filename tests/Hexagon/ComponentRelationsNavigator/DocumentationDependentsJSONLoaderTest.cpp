
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
        "quintessence/Hexagon/AdvancedCodeEditor/Stage",
        "quintessence/Hexagon/BuildSequenceMeter/Renderer",
        "quintessence/Hexagon/CodeEditor/Stage",
        "quintessence/Hexagon/ComponentRelationsNavigator/Stage",
        "quintessence/Hexagon/Elements/ListMenu",
        "quintessence/Hexagon/Elements/QuoteRenderer",
        "quintessence/Hexagon/Elements/StageInfoOverlay",
        "quintessence/Hexagon/Font",
        "quintessence/Hexagon/LayoutToStagesCreator",
        "quintessence/Hexagon/Logo",
        "quintessence/Hexagon/MissingFile/Stage",
        "quintessence/Hexagon/StageFactory",
        "quintessence/Hexagon/TitleScreen",
        "quintessence/Hexagon/UI/DrawingBox",
        "quintessence/Hexagon/UI/LittleMenu",
      };

   EXPECT_EQ(expected_list, documentation_dependents_jsonloader.build_dependent_names_for_component_name());
}

