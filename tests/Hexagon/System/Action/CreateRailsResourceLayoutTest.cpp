
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
   std::vector<StageInterface *> stages;
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout(stages);

   EXPECT_EQ(0, stages.size());

   EXPECT_TRUE(create_rails_resource_layout.execute());

   EXPECT_EQ(1, stages.size());
}



TEST(Hexagon_System_Action_CreateRailsResourceLayoutTest, execute___created_stages_have_the_expected_placement)
{
   std::vector<StageInterface *> stages;
   Hexagon::System::Action::CreateRailsResourceLayout create_rails_resource_layout(stages);

   EXPECT_TRUE(create_rails_resource_layout.execute());

   ASSERT_EQ(1, stages.size());

   placement3d expected_place(0, 0, 0);
   expected_place.size = vec3d(400, 650, 0);
   expected_place.align = vec3d(0.5, 0.5, 0.0);
   expected_place.rotation = vec3d(0.0, 0.0, 0.0);

   placement3d actual_place = stages[0]->get_place();

   EXPECT_EQ(expected_place.size, actual_place.size);
   EXPECT_EQ(expected_place.position, actual_place.position);
   EXPECT_EQ(expected_place.align, actual_place.align);
   EXPECT_EQ(expected_place.rotation, actual_place.rotation);
   EXPECT_EQ(expected_place.scale, actual_place.scale);
}

