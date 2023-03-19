
#include <gtest/gtest.h>

#include <Hexagon/ComponentDependencies.hpp>


TEST(Hexagon_ComponentDependenciesTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentDependencies component_dependencies;
}


TEST(Hexagon_ComponentDependenciesTest, generate_dependency_filename__returns_the_expected_filename)
{
   Hexagon::ComponentDependencies component_dependencies("This/Is/The/Component");
   std::string expected_string = "deps/This/Is/The/Component.d";
   EXPECT_EQ(expected_string, component_dependencies.generate_dependency_filename());
}


