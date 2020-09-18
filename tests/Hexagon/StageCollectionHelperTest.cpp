
#include <gtest/gtest.h>

#include <Hexagon/StageCollectionHelper.hpp>

TEST(Hexagon_StageCollectionHelperTest, can_be_created_without_blowing_up)
{
   Hexagon::StageCollectionHelper stage_collection_helper;
}

TEST(Hexagon_StageCollectionHelperTest, run__returns_the_expected_response)
{
   std::vector<StageInterface *> stages = {};
   Hexagon::StageCollectionHelper stage_collection_helper(&stages);

   std::vector<StageInterface *> expected_collection = {};
   std::vector<StageInterface *> actual_collection = stage_collection_helper.all();

   EXPECT_EQ(expected_collection, actual_collection);
}

