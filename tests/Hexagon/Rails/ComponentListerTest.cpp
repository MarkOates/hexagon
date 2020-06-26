
#include <gtest/gtest.h>

#include <Hexagon/Rails/ComponentLister.hpp>

TEST(Hexagon_Rails_ComponentListerTest, can_be_created_without_blowing_up)
{
   Hexagon::Rails::ComponentLister component_lister;
}

TEST(Hexagon_Rails_ComponentListerTest, components__returns_the_expected_list_of_components)
{
   Hexagon::Rails::ComponentLister component_lister;
   std::vector<std::string> expected_components = {};
   EXPECT_EQ(expected_components, component_lister.components());
}
