
#include <gtest/gtest.h>

#include <Hexagon/StageCollectionHelper.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

TEST(Hexagon_StageCollectionHelperTest, can_be_created_without_blowing_up)
{
   Hexagon::StageCollectionHelper stage_collection_helper;
}

TEST(Hexagon_StageCollectionHelperTest, all__without_stages__raises_an_exception)
{
   Hexagon::StageCollectionHelper stage_collection_helper;
   ASSERT_THROW_GUARD_ERROR(
      stage_collection_helper.all(),
      "Hexagon::StageCollectionHelper::all",
      "stages"
   );
}

TEST(Hexagon_StageCollectionHelperTest, all__returns_all_of_the_stages)
{
   std::vector<StageInterface *> stages = {};
   Hexagon::StageCollectionHelper stage_collection_helper(&stages);

   std::vector<StageInterface *> expected_collection = {};
   std::vector<StageInterface *> actual_collection = stage_collection_helper.all();

   EXPECT_EQ(expected_collection, actual_collection);
}

TEST(Hexagon_StageCollectionHelperTest, count_code_editor_stages__returns_the_number_of_code_editor_stages)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_all_code_editor_stages_as_code_editor_stages__returns_all_the_code_editor_stages)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_all_advanced_code_editor_stages__returns_all_the_advanced_code_editor_stages)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_all_code_editor_stages_as_code_editor_stages__preserves_the_initial_order_of_the_stages)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_all_render_on_hud_stages__returns_all_the_stages_that_have_the_render_on_hud_flag_set_to_true)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_all_stages_not_rendered_on_hud__returns_all_the_stages_that_have_the_render_on_hud_flag_set_to_false)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_frontmost_advanced_code_editor_stage__returns_the_frontmost_advanced_code_editor_stage)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_frontmost_advanced_code_editor_stage__returns_nullptr_if_the_frontmost_stage_is_not_an_advanced_code_editor)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_frontmost_code_editor_stage__returns_the_frontmost_stage_if_it_is_a_code_editor_type)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   get_frontmost_git_commit_message_input_box__returns_the_frontmost_stage_if_it_is_a_git_commit_message_box)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest, get_frontmost_stage__returns_the_stage_at_the_back_of_the_collection)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   is_frontmost_stage_a_regex_input_box__returns_true_if_the_frontmost_stage_is_a_regex_input_box)
{
   // TODO
}

TEST(Hexagon_StageCollectionHelperTest,
   is_frontmost_stage_a_regex_input_box__returns_false_if_the_frontmost_stage_is_not_a_regex_input_box)
{
   // TODO
}

