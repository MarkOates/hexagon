
#include <gtest/gtest.h>

#include <Hexagon/Layout.hpp>

TEST(Hexagon_LayoutTest, can_be_created_without_blowing_up)
{
   Hexagon::Layout layout;
}

TEST(Hexagon_LayoutTest, create__will_create_the_passed_files)
{
   std::string concept_name = "Hexagon/Logo";
   std::vector<StageInterface *> stages;
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Logo.q.yml", "blast_quintessence", placement3d(0, 0, 0) },
   };

   Hexagon::Layout layout(concept_name, &stages, files, daemus_command);

   layout.create();

   ASSERT_EQ(false, stages.empty());
}

TEST(Hexagon_LayoutTest, create__will_create_code_editor_stages_for_the_passed_files)
{
   std::string concept_name = "Hexagon/Logo";
   std::vector<StageInterface *> stages;
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/Users/markoates/Repos/hexagon/quintessence/Hexagon/Logo.q.yml", "blast_quintessence", placement3d(0, 0, 0) },
      { "/Users/markoates/Repos/hexagon/tests/Hexagon/LogoTest.cpp", "blast_test", placement3d(0, 0, 0) },
   };

   Hexagon::Layout layout(concept_name, &stages, files, daemus_command);

   layout.create();

   ASSERT_EQ(files.size(), stages.size());

   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::CODE_EDITOR, stage->get_type());
   }
}

TEST(Hexagon_LayoutTest, create__will_create_missing_file_stages_for_files_that_do_not_exist)
{
   std::string concept_name = "- Missing Files -";
   std::vector<StageInterface *> stages;
   std::string daemus_command = "git diff";
   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/A/Path/To/A/File/ThatDoesNotExist.cpp", "blast_quintessence", placement3d(0, 0, 0) },
      { "/Another/Path/To/A/NonExistentFile.cpp", "blast_test", placement3d(0, 0, 0) },
   };

   Hexagon::Layout layout(concept_name, &stages, files, daemus_command);

   layout.create();

   ASSERT_EQ(files.size(), stages.size());

   for (auto &stage : stages)
   {
      EXPECT_EQ(StageInterface::MISSING_FILE, stage->get_type());
   }
}

TEST(Hexagon_LayoutTest, create__will_position_the_stages_at_the_passed_placement)
{
   std::string concept_name = "- Mixed Files -";
   std::vector<StageInterface *> stages;
   std::string daemus_command = "git diff";

   std::vector<std::tuple<std::string, std::string, placement3d>> files = {
      { "/Users/markoates/Repos/hexagon/tests/Hexagon/LogoTest.cpp", "blast_test", placement3d(147, 1920, 640) },
      { "/A/Path/To/A/File/ThatDoesNotExist.cpp", "blast_quintessence", placement3d(69, 420, 89) },
   };

   Hexagon::Layout layout(concept_name, &stages, files, daemus_command);

   layout.create();

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

