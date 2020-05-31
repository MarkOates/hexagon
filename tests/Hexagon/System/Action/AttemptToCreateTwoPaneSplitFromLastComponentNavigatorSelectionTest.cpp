
#include <gtest/gtest.h>

#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>

typedef Hexagon::System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection CreateTwoSplit;

#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/MissingFile/Stage.hpp>

TEST(Hexagon_System_Action_AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelectionTest, can_be_created_without_blowing_up)
{
   CreateTwoSplit create_two_split_action;
}

TEST(Hexagon_System_Action_AttemptTo, execute__creates_two_stages_with_the_expected_size)
{
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Elements/Frame";
   int code_editor_width = 234;

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages, code_editor_width);

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());

   for (auto &stage : stages)
   {
      placement3d &place = stage->get_place();
      EXPECT_EQ(code_editor_width, place.size.x);
   }

   SUCCEED();
}

TEST(Hexagon_System_Action_AttemptTo, execute__with_a_valid_component_creats_two_code_editor_stages)
{
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Elements/Frame";

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
   std::string component_name = "Hexagon/Elements/Frame";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages);

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());

   std::string expected_quintessence_filename = "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Elements/Frame.q.yml";
   std::string expected_test_filename = "/Users/markoates/Repos/hexagon/tests/Hexagon/Elements/FrameTest.cpp";

   ASSERT_EQ(StageInterface::CODE_EDITOR, stages[0]->get_type());
   EXPECT_EQ(expected_test_filename, static_cast<::CodeEditor::CodeEditor*>(stages[0])->get_filename());

   ASSERT_EQ(StageInterface::CODE_EDITOR, stages[1]->get_type());
   EXPECT_EQ(expected_quintessence_filename, static_cast<::CodeEditor::CodeEditor*>(stages[1])->get_filename());
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
      EXPECT_EQ(StageInterface::MISSING_FILE, stage->get_type());
   }
}

TEST(Hexagon_System_Action_AttemptTo, execute__will_set_the_expected_filename_when_creating_missing_file_stages)
{
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/ComponentThatIsNotPresent";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages);

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());

   Hexagon::MissingFile::Stage &missing_quintessence_file_stage = *static_cast<Hexagon::MissingFile::Stage *>(stages[1]);
   Hexagon::MissingFile::Stage &missing_test_file_stage = *static_cast<Hexagon::MissingFile::Stage *>(stages[0]);

   EXPECT_EQ("/Users/markoates/Repos/hexagon/quintessence/Hexagon/ComponentThatIsNotPresent.q.yml",
             missing_quintessence_file_stage.get_expected_filename());
   EXPECT_EQ("/Users/markoates/Repos/hexagon/tests/Hexagon/ComponentThatIsNotPresentTest.cpp",
             missing_test_file_stage.get_expected_filename());
}

