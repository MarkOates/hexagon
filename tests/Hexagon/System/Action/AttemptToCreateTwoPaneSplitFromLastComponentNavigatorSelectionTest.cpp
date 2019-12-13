
#include <gtest/gtest.h>

#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>

typedef Hexagon::System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection CreateTwoSplit;

#include <Hexagon/CodeEditor/Stage.hpp>

TEST(Hexagon_System_Action_AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelectionTest, can_be_created_without_blowing_up)
{
   CreateTwoSplit create_two_split_action;
}

TEST(Hexagon_System_Action_AttemptTo, execute__creates_two_stages)
{
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Frame";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages);

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());
}

TEST(Hexagon_System_Action_AttemptTo, execute__with_a_valid_component_creats_two_code_editor_stages)
{
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Frame";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages);

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());
   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::CODE_EDITOR, stage->get_type());
   }
}

TEST(Hexagon_System_Action_AttemptTo, execute__with_a_valid_component_opens_the_quintessence_and_test_file)
{
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Frame";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages);

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());

   std::string expected_quintessence_filename = "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Frame.q.yml";
   std::string expected_test_filename = "/Users/markoates/Repos/hexagon/tests/Hexagon/FrameTest.cpp";

   ASSERT_EQ(StageInterface::CODE_EDITOR, stages[0]->get_type());
   EXPECT_EQ(expected_test_filename, static_cast<CodeEditor::Stage*>(stages[0])->get_filename());

   ASSERT_EQ(StageInterface::CODE_EDITOR, stages[1]->get_type());
   EXPECT_EQ(expected_quintessence_filename, static_cast<CodeEditor::Stage*>(stages[1])->get_filename());
}

TEST(Hexagon_System_Action_AttemptTo, execute__positions_two_stages_at_expected_placements)
{
   //skip
}

TEST(Hexagon_System_Action_AttemptTo, execute__if_files_are_missing_will_create_missing_file_stages)
{
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/ComponentThatIsNotPresent";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages);

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());
   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::FILE_MISSING, stage->get_type());
   }
}
