
#include <gtest/gtest.h>

#include <Hexagon/CodeMessagePoint.hpp>

TEST(CodeMessagePointTest, can_be_created_without_blowing_up)
{
   CodeMessagePoint code_message_point;
}

TEST(CodeMessagePointTest, has_an_equality_operator)
{
   ASSERT_EQ(CodeMessagePoint(), CodeMessagePoint());
}

