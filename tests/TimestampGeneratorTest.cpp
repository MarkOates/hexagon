
#include <gtest/gtest.h>

#include <TimestampGenerator.hpp>

TEST(TimestampGeneratorTest, can_be_created_without_blowing_up)
{
   TimestampGenerator timestamp_generator;
}

TEST(TimestampGeneratorTest, get_current_time__will_generate_a_string_with_the_current_time)
{
   TimestampGenerator timestamp_generator;
   //EXPECT_EQ("asdf", timestamp_generator.get_current_time());
}

