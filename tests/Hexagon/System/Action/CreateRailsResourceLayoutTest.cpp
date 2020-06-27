
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CreateRailsResourceLayout.hpp>



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout;
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, run__returns_the_expected_response)
{
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, create_rails_resource_layout.run());
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, execute__returns_successful)
{
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout;

   EXPECT_TRUE(create_rails_resource_layout.execute());
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, execute___expected_layout_is_created)
{
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout;

   EXPECT_TRUE(create_rails_resource_layout.execute());
}

