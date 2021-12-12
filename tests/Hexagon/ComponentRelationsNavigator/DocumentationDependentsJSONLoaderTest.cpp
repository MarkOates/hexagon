
#include <gtest/gtest.h>

#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>

TEST(Hexagon_ComponentRelationsNavigator_DocumentationDependentsJSONLoaderTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader documentation_dependents_jsonloader;
}

TEST(Hexagon_ComponentRelationsNavigator_DocumentationDependentsJSONLoaderTest, run__returns_the_expected_response)
{
   Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader documentation_dependents_jsonloader;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, documentation_dependents_jsonloader.run());
}
