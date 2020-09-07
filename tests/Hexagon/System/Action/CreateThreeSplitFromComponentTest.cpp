
#include <gtest/gtest.h>

#include <Hexagon/System/Action/CreateThreeSplitFromComponent.hpp>

#include <Hexagon/MissingFile/Stage.hpp>
#include <Hexagon/StageFactory.hpp>

typedef Hexagon::System::Action::CreateThreeSplitFromComponent CreateThreeSplit;

class Hexagon_System_Action_CreateThreeSplitFromComponentTestWithEmptyFixture : public ::testing::Test
{};

static std::string TEST_FIXTURE_DIRECTORY_ROOT = "/Users/markoates/Repos/hexagon/tests/fixtures/";
static const std::string TEST_FIXTURE_CONFIG_FILENAME = TEST_FIXTURE_DIRECTORY_ROOT + "hexagon.test.cfg";

#include <Testing/WithStageFactoryFixture.hpp>

class Hexagon_System_Action_CreateThreeSplitFromComponentTestWithFixture : public Testing::WithStageFactoryFixture
{};

TEST_F(Hexagon_System_Action_CreateThreeSplitFromComponentTestWithEmptyFixture,
   can_be_created_without_blowing_up)
{
   Hexagon::System::Action::CreateThreeSplitFromComponent create_three_split_from_component;
}

TEST_F(Hexagon_System_Action_CreateThreeSplitFromComponentTestWithFixture,
   execute__creates_three_stages_split_across_the_width)
{
   std::string project_path = "/Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/Action";
   std::vector<StageInterface *> stages;
   int code_editor_width = 234;
   CreateThreeSplit create_three_split(
      project_path,
      component,
      stages,
      &get_stage_factory_ref(),
      200,
      100,
      code_editor_width
   );
   EXPECT_EQ(true, create_three_split.execute());
   ASSERT_EQ(3, stages.size());

   for (auto &stage : stages)
   {
      placement3d &place = stage->get_place();
      ASSERT_EQ(code_editor_width, place.size.x);
   }
}

TEST_F(Hexagon_System_Action_CreateThreeSplitFromComponentTestWithFixture,
   execute__with_a_valid_component_creates_the_expected_files)
{
   std::string project_path = "/Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/System/Action/CreateThreeSplitFromComponent";
   std::vector<StageInterface *> stages;

   CreateThreeSplit create_three_split(project_path, component, stages, &get_stage_factory_ref());

   EXPECT_EQ(true, create_three_split.execute());

   ASSERT_EQ(3, stages.size());
   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::CODE_EDITOR, stage->get_type());
   }
}

TEST_F(Hexagon_System_Action_CreateThreeSplitFromComponentTestWithFixture,
   execute__with_an_invalid_component_creates_missing_file_stages)
{
   std::string project_path = "/Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/AComponentThatDoesNotExist";
   std::vector<StageInterface *> stages;

   CreateThreeSplit create_three_split(project_path, component, stages, &get_stage_factory_ref());

   EXPECT_EQ(true, create_three_split.execute());

   ASSERT_EQ(3, stages.size());
   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::MISSING_FILE, stage->get_type());
   }
}

TEST_F(Hexagon_System_Action_CreateThreeSplitFromComponentTestWithFixture,
   execute__with_an_invalid_component_sets_the_expected_filename_on_the_missing_file_stage)
{
   std::string project_path = "/Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/AComponentThatDoesNotExist";
   std::vector<StageInterface *> stages;

   CreateThreeSplit create_three_split(project_path, component, stages, &get_stage_factory_ref());

   EXPECT_EQ(true, create_three_split.execute());

   ASSERT_EQ(3, stages.size());

   Hexagon::MissingFile::Stage &missing_header_file_stage = *static_cast<Hexagon::MissingFile::Stage *>(stages[0]);
   Hexagon::MissingFile::Stage &missing_source_file_stage = *static_cast<Hexagon::MissingFile::Stage *>(stages[1]);
   Hexagon::MissingFile::Stage &missing_test_file_stage = *static_cast<Hexagon::MissingFile::Stage *>(stages[2]);

   EXPECT_EQ("/Users/markoates/Repos/hexagon/include/Hexagon/AComponentThatDoesNotExist.hpp",
             missing_header_file_stage.get_expected_filename());
   EXPECT_EQ("/Users/markoates/Repos/hexagon/src/Hexagon/AComponentThatDoesNotExist.cpp",
             missing_source_file_stage.get_expected_filename());
   EXPECT_EQ("/Users/markoates/Repos/hexagon/tests/Hexagon/AComponentThatDoesNotExistTest.cpp",
             missing_test_file_stage.get_expected_filename());
}

TEST_F(Hexagon_System_Action_CreateThreeSplitFromComponentTestWithFixture,
   execute__places_the_stages_in_the_expected_positions)
{
   std::string project_path = "/Users/markoates/Repos/hexagon/";
   std::string component = "Hexagon/System/Action/CreateThreeSplitFromComponent";
   std::vector<StageInterface *> stages;
   float display_width = 300;
   int code_editor_width = 234;

   CreateThreeSplit create_three_split(
      project_path,
      component,
      stages,
      &get_stage_factory_ref(),
      display_width,
      100,
      code_editor_width
   );

   EXPECT_EQ(true, create_three_split.execute());

   ASSERT_EQ(3, stages.size());

   ASSERT_EQ(-234, stages[0]->get_place().position.x);
   ASSERT_EQ(0, stages[1]->get_place().position.x);
   ASSERT_EQ(234, stages[2]->get_place().position.x);
}
