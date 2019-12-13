
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>

typedef Hexagon::System::Action::CreateThreeSplitFromComponent CreateThreeSplit;

TEST(Hexagon_System_Action_CreateThreeSplitFromComponentTest, can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CreateThreeSplitFromComponent create_three_split_from_component;
}

TEST(Hexagon_System_Action_CreateThreeSplitFromComponentTest, execute__creates_three_stages_split_across_the_width)
{
   std::string project_path = "Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/Action";
   std::vector<StageInterface *> stages;
   CreateThreeSplit create_three_split(project_path, component, stages);
   EXPECT_EQ(true, create_three_split.execute());
   ASSERT_EQ(3, stages.size());
}

TEST(Hexagon_System_Action_CreateThreeSplitTest, execute__with_a_valid_component_creates_the_expected_files)
{
   std::string project_path = "Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/Action";
   std::vector<StageInterface *> stages;

   CreateThreeSplit create_three_split(project_path, component, stages);

   EXPECT_EQ(true, create_three_split.execute());

   ASSERT_EQ(3, stages.size());
   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::CODE_EDITOR, stage->get_type());
   }
}
