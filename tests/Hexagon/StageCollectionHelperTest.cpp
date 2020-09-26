
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/StageCollectionHelper.hpp>

TEST(Hexagon_StageCollectionHelperTest, can_be_created_without_blowing_up)
{
   Hexagon::StageCollectionHelper stage_collection_helper;
}

TEST(Hexagon_StageCollectionHelperTest, all__without_stages__raises_an_exception)
{
   Hexagon::StageCollectionHelper stage_collection_helper;
   std::string expected_error_message = "StageCollectionHelper::all: error: guard \"stages\" not met";
   ASSERT_THROW_WITH_MESSAGE(stage_collection_helper.all(), std::runtime_error, expected_error_message);
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
   get_all_code_editor_stages_as_code_editor_stages__preserves_the_initial_order_of_the_stages)
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

