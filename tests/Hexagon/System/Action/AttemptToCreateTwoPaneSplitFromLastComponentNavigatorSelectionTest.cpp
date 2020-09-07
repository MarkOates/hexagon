
#include <gtest/gtest.h>

#include <Hexagon/System/Action/AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection.hpp>

typedef Hexagon::System::Action::AttemptToCreateTwoPaneSplitFromLastComponentNavigatorSelection CreateTwoSplit;

#include <Hexagon/CodeEditor/CodeEditor.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Hexagon/MissingFile/Stage.hpp>

class Hexagon_System_Action_CreateTwoSplitTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithStageFactoryFixture.hpp>

class Hexagon_System_Action_CreateTwoSplitTestWithFixture : public Testing::WithStageFactoryFixture
{};

TEST_F(Hexagon_System_Action_CreateTwoSplitTestWithEmptyFixture,
   can_be_created_without_blowing_up)
{
   CreateTwoSplit create_two_split_action;
}

TEST_F(Hexagon_System_Action_CreateTwoSplitTestWithFixture,
   execute__creates_two_stages_with_the_expected_size)
{
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Elements/Frame";
   int code_editor_width = 234;

   CreateTwoSplit create_two_split(
      home_directory,
      component_name,
      2430,
      1350,
      stages,
      &get_stage_factory_ref(),
      code_editor_width
   );

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());

   for (auto &stage : stages)
   {
      placement3d &place = stage->get_place();
      EXPECT_EQ(code_editor_width, place.size.x);
   }

   al_destroy_display(display);
   SUCCEED();
}

TEST_F(Hexagon_System_Action_CreateTwoSplitTestWithFixture,
   execute__with_a_valid_component_creats_two_code_editor_stages)
{
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Elements/Frame";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages, &get_stage_factory_ref());

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());
   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::CODE_EDITOR, stage->get_type());
   }
   al_destroy_display(display);
}

TEST_F(Hexagon_System_Action_CreateTwoSplitTestWithFixture,
   execute__with_a_valid_component_opens_the_quintessence_and_test_file)
{
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/Elements/Frame";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages, &get_stage_factory_ref());

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());

   std::string expected_quintessence_filename =
      "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Elements/Frame.q.yml";
   std::string expected_test_filename = "/Users/markoates/Repos/hexagon/tests/Hexagon/Elements/FrameTest.cpp";

   ASSERT_EQ(StageInterface::CODE_EDITOR, stages[0]->get_type());
   std::string actual_test_filename =
      static_cast<Hexagon::CodeEditor::Stage*>(stages[0])->get_code_editor_ref().get_filename();
   EXPECT_EQ(expected_test_filename,actual_test_filename);

   ASSERT_EQ(StageInterface::CODE_EDITOR, stages[1]->get_type());
   std::string actual_quintessence_filename =
      static_cast<Hexagon::CodeEditor::Stage*>(stages[1])->get_code_editor_ref().get_filename();
   EXPECT_EQ(expected_quintessence_filename, actual_quintessence_filename);
   al_destroy_display(display);
}

TEST_F(Hexagon_System_Action_CreateTwoSplitTestWithEmptyFixture,
   execute__positions_two_stages_at_expected_placements)
{
   //skip
}

TEST_F(Hexagon_System_Action_CreateTwoSplitTestWithFixture,
   execute__if_files_are_missing_will_create_missing_file_stages)
{
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/ComponentThatIsNotPresent";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages, &get_stage_factory_ref());

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());
   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::MISSING_FILE, stage->get_type());
   }
   al_destroy_display(display);
}

TEST_F(Hexagon_System_Action_CreateTwoSplitTestWithFixture,
   execute__will_set_the_expected_filename_when_creating_missing_file_stages)
{
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
   std::vector<StageInterface *> stages;
   std::string home_directory = "/Users/markoates/Repos/hexagon/";
   std::string component_name = "Hexagon/ComponentThatIsNotPresent";

   CreateTwoSplit create_two_split(home_directory, component_name, 2430, 1350, stages, &get_stage_factory_ref());

   create_two_split.execute();
   EXPECT_EQ(2, stages.size());

   Hexagon::MissingFile::Stage &missing_quintessence_file_stage = *static_cast<Hexagon::MissingFile::Stage *>(stages[1]);
   Hexagon::MissingFile::Stage &missing_test_file_stage = *static_cast<Hexagon::MissingFile::Stage *>(stages[0]);

   EXPECT_EQ("/Users/markoates/Repos/hexagon/quintessence/Hexagon/ComponentThatIsNotPresent.q.yml",
             missing_quintessence_file_stage.get_expected_filename());
   EXPECT_EQ("/Users/markoates/Repos/hexagon/tests/Hexagon/ComponentThatIsNotPresentTest.cpp",
             missing_test_file_stage.get_expected_filename());
   al_destroy_display(display);
}

