
#include <gtest/gtest.h>

#include <Testing/WithStageFactoryFixture.hpp>

TEST(Testing_WithStageFactoryFixtureTest, can_be_created_without_blowing_up)
{
   Testing::WithStageFactoryFixture with_stage_factory_fixture;
}

TEST(Testing_WithStageFactoryFixtureTest, run__returns_the_expected_response)
{
   Testing::WithStageFactoryFixture with_stage_factory_fixture;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, with_stage_factory_fixture.run());
}
