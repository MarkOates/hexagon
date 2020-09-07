
#include <gtest/gtest.h>

#include <Hexagon/LayoutToStagesCreator.hpp>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <Hexagon/AdvancedCodeEditor/Stage.hpp>

class Hexagon_LayoutToStagesCreatorTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithStageFactoryFixture.hpp>

class Hexagon_LayoutToStagesCreatorTestWithFixture : public Testing::WithStageFactoryFixture
{};

TEST_F(Hexagon_LayoutToStagesCreatorTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::LayoutToStagesCreator layout_to_stage_creator;
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture, create__will_create_the_passed_files)
{
   std::vector<StageInterface *> stages;

   std::string concept_name = "Hexagon/Logo";
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Logo.q.yml", "blast_quintessence", placement3d(0, 0, 0) },
   };

   Hexagon::Layout layout(concept_name, files, daemus_command);

   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      &get_stage_factory_ref(),
      &layout,
      &get_font_bin_ref()
   );

   layout_to_stage_creator.create();

   ASSERT_EQ(false, stages.empty());
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   create__will_create_advanced_code_editor_stages_for_the_passed_files)
{
   std::vector<StageInterface *> stages;

   std::string concept_name = "Hexagon/Logo";
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Logo.q.yml", "blast_quintessence", placement3d(0, 0, 0) },
      { "/Users/markoates/Repos/hexagon/tests/Hexagon/LogoTest.cpp", "blast_test", placement3d(0, 0, 0) },
   };

   Hexagon::Layout layout(concept_name, files, daemus_command);

   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      &get_stage_factory_ref(),
      &layout,
      &get_font_bin_ref()
   );

   layout_to_stage_creator.create();

   ASSERT_EQ(files.size(), stages.size());

   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::ADVANCED_CODE_EDITOR, stage->get_type());
   }
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   create__will_initialize_the_created_advanced_code_editor_stages_and_set_the_expected_properties_on_it)
{
   std::vector<StageInterface *> stages;

   std::string concept_name = "Hexagon/Logo";
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Logo.q.yml", "blast_quintessence", placement3d(0, 0, 0) },
      { "/Users/markoates/Repos/hexagon/tests/Hexagon/LogoTest.cpp", "blast_test", placement3d(0, 0, 0) },
   };

   Hexagon::Layout layout(concept_name, files, daemus_command);

   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      &get_stage_factory_ref(),
      &layout,
      &get_font_bin_ref()
   );

   layout_to_stage_creator.create();

   ASSERT_EQ(files.size(), stages.size());

   for (auto &stage : stages)
   {
      Hexagon::AdvancedCodeEditor::Stage *advanced_code_editor_stage =
         static_cast<Hexagon::AdvancedCodeEditor::Stage *>(stage);
      EXPECT_EQ(true, advanced_code_editor_stage->get_initialized());
      EXPECT_EQ(false, advanced_code_editor_stage->get_lines().empty());
   }
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   create__will_create_missing_file_stages_for_files_that_do_not_exist)
{
   std::vector<StageInterface *> stages;

   std::string concept_name = "- Missing Files -";
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/A/Path/To/A/File/ThatDoesNotExist.cpp", "blast_quintessence", placement3d(0, 0, 0) },
      { "/Another/Path/To/A/NonExistentFile.cpp", "blast_test", placement3d(0, 0, 0) },
   };

   Hexagon::Layout layout(concept_name, files, daemus_command);

   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      &get_stage_factory_ref(),
      &layout,
      &get_font_bin_ref()
   );

   layout_to_stage_creator.create();

   ASSERT_EQ(files.size(), stages.size());

   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::MISSING_FILE, stage->get_type());
   }
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   create__will_position_the_stages_at_the_passed_placement)
{
   std::vector<StageInterface *> stages;

   std::string concept_name = "- Mixed Files -";
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/Users/markoates/Repos/hexagon/tests/Hexagon/LogoTest.cpp", "blast_test", placement3d(147, 1920, 640) },
      { "/A/Path/To/A/File/ThatDoesNotExist.cpp", "blast_quintessence", placement3d(69, 420, 89) },
   };

   Hexagon::Layout layout(concept_name, files, daemus_command);

   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      &get_stage_factory_ref(),
      &layout,
      &get_font_bin_ref()
   );

   layout_to_stage_creator.create();

   ASSERT_EQ(2, stages.size());
   placement3d first_stage_placement = stages[0]->get_place();
   placement3d second_stage_placement = stages[1]->get_place();

   placement3d expected_first_stage_placement = std::get<2>(files[0]);
   placement3d expected_second_stage_placement = std::get<2>(files[1]);

   EXPECT_EQ(expected_first_stage_placement.position, first_stage_placement.position);
   EXPECT_EQ(expected_first_stage_placement.rotation, first_stage_placement.rotation);
   EXPECT_EQ(expected_first_stage_placement.scale, first_stage_placement.scale);

   EXPECT_EQ(expected_second_stage_placement.position, second_stage_placement.position);
   EXPECT_EQ(expected_second_stage_placement.rotation, second_stage_placement.rotation);
   EXPECT_EQ(expected_second_stage_placement.scale, second_stage_placement.scale);
}

