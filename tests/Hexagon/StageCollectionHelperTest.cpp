
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/StageCollectionHelper.hpp>

void foo() {};

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
