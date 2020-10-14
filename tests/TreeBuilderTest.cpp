
#include <gtest/gtest.h>

#include <TreeBuilder.hpp>

TEST(TreeBuilderTest, can_be_created_without_blowing_up)
{
   TreeBuilder tree_builder;
}

TEST(TreeBuilderTest, run__returns_the_expected_response)
{
   TreeBuilder tree_builder;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, tree_builder.run());
}
