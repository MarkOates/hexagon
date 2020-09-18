
#include <gtest/gtest.h>

#include <Hexagon/StageCollectionHelper.hpp>

TEST(Hexagon_StageCollectionHelperTest, can_be_created_without_blowing_up)
{
   Hexagon::StageCollectionHelper stage_collection_helper;
}

TEST(Hexagon_StageCollectionHelperTest, run__returns_the_expected_response)
{
   Hexagon::StageCollectionHelper stage_collection_helper;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, stage_collection_helper.run());
}

