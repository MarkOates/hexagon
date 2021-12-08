
#include <gtest/gtest.h>

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>

TEST(Hexagon_ComponentRelationsNavigator_ComponentRelationsTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations;
}

TEST(Hexagon_ComponentRelationsNavigator_ComponentRelationsTest, run__returns_the_expected_response)
{
   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, component_relations.run());
}
