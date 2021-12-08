
#include <gtest/gtest.h>

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>


TEST(Hexagon_ComponentRelationsNavigator_ComponentRelationsTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations;
}


TEST(Hexagon_ComponentRelationsNavigator_ComponentRelationsTest, build_dependents__returns_the_class_dependents)
{
   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations;
   std::vector<Blast::Project::Component> expected_components = {};
   // TODO
   //EXPECT_EQ(expected_components, component_relations.build_dependents());
}


