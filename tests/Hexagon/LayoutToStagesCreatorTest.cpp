
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <Hexagon/LayoutToStagesCreator.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

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

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   place_and_load_code_editor__without_stages__raises_the_expected_error_message)
{
   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      nullptr,
      &get_stage_factory_ref()
      //&layout,
      //&get_font_bin_ref()
   );

   ASSERT_THROW_GUARD_ERROR(
      layout_to_stage_creator.place_and_load_code_editor(),
      "Hexagon::LayoutToStagesCreator::place_and_load_code_editor",
      "stages"
   );
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   place_and_load_code_editor__without_a_stage_factory__raises_the_expected_error_message)
{
   std::vector<StageInterface *> stages;
   Hexagon::Layout layout;
   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      nullptr,
      &layout,
      &get_font_bin_ref()
   );

   ASSERT_THROW_GUARD_ERROR(
      layout_to_stage_creator.place_and_load_code_editor(),
      "Hexagon::LayoutToStagesCreator::place_and_load_code_editor",
      "stage_factory"
   );
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   place_and_load_code_editor__without_a_layout__raises_the_expected_error_message)
{
   std::vector<StageInterface *> stages;
   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      &get_stage_factory_ref(),
      nullptr,
      &get_font_bin_ref()
   );

   ASSERT_THROW_GUARD_ERROR(
      layout_to_stage_creator.place_and_load_code_editor(),
      "Hexagon::LayoutToStagesCreator::place_and_load_code_editor",
      "layout"
   );
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   place_and_load_code_editor__without_a_font_bin__raises_the_expected_error_message)
{
   std::vector<StageInterface *> stages;
   Hexagon::Layout layout;
   Hexagon::LayoutToStagesCreator layout_to_stage_creator(
      &stages,
      &get_stage_factory_ref(),
      &layout,
      nullptr
   );

   ASSERT_THROW_GUARD_ERROR(
      layout_to_stage_creator.place_and_load_code_editor(),
      "Hexagon::LayoutToStagesCreator::place_and_load_code_editor",
      "font_bin"
   );
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

   // collect and assert on types
   std::vector<StageInterface::type_t> types;
   for (auto &stage : stages) types.push_back(stage->get_type());
   ASSERT_THAT(types, testing::Each(StageInterface::ADVANCED_CODE_EDITOR));

   // assert expected initialization
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
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
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
   al_destroy_display(display);
}

TEST_F(Hexagon_LayoutToStagesCreatorTestWithFixture,
   create__will_position_the_stages_at_the_passed_placement)
{
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080); // TODO: remove this hack.  This is only required because
                                                             // the factory uses al_get_display_width|height functions
                                                             // which it should not do.  Rather, the dimensions of the
                                                             // surface should be passed in if position is relative to
                                                             // it.  That was a dirty hack for then, and the display
                                                             // here is a second-order hack to get this test passing.
                                                             // Eventually this should be fixed.
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
   al_destroy_display(display);
}

