
#include <gtest/gtest.h>

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>


TEST(Hexagon_ComponentRelationsNavigator_ComponentRelationsTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations;
}


TEST(Hexagon_ComponentRelationsNavigator_ComponentRelationsTest, build_dependents__returns_the_class_dependents)
{
   //Blast::Project::Component component("AllegroFlare/FontBin", "allegro_flare");
   Blast::Project::Component component("Hexagon/PacketRenderer", "/Users/markoates/Repos/hexagon");
   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations(component);

   std::vector<std::string> expected_component_dependents_names = { "Hexagon/Hud" };
   std::vector<std::string> actual_component_dependents_names = component_relations.build_dependents_list();

   EXPECT_EQ(expected_component_dependents_names, actual_component_dependents_names);
}


TEST(Hexagon_ComponentRelationsNavigator_ComponentRelationsTest, build_dependencies__returns_the_class_dependencies)
{
   //Blast::Project::Component component("AllegroFlare/FontBin", "allegro_flare");
   Blast::Project::Component component("Hexagon/PacketRenderer", "/Users/markoates/Repos/hexagon");
   Hexagon::ComponentRelationsNavigator::ComponentRelations component_relations(component);

   std::vector<std::string> expected_component_dependencies_names = {
      "AllegroFlare/Bin",
      "AllegroFlare/ConsoleColor",
      "AllegroFlare/FontBin",
      "Hexagon/Elements/Window",
      "Hexagon/Packet",
      "allegro_flare/placement2d",
      "allegro_flare/vec2b",
      "allegro_flare/vec2d",
   };
   std::vector<std::string> actual_component_dependencies_names = component_relations.build_dependencies_list();

   EXPECT_EQ(expected_component_dependencies_names, actual_component_dependencies_names);
}


