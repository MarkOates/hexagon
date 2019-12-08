
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>

TEST(Hexagon_System_Action_CreateThreeSplitFromComponentTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CreateThreeSplitFromComponent create_three_split_from_component;
}

TEST(Hexagon_System_Action_CreateThreeSplitFromComponentTest, execute__creates_three_stages_split_across_the_width)
{
   Hexagon::System::Action::CreateThreeSplitFromComponent create_three_split_from_component;
   EXPECT_EQ(true, create_three_split_from_component.execute());
}
