
#include <gtest/gtest.h>

#include <Hexagon/Forms/Fun.hpp>

TEST(Hexagon_Forms_FunTest, can_be_created_without_blowing_up)
{
   Hexagon::Forms::Fun fun;
}

TEST(Hexagon_Forms_FunTest, run__returns_the_expected_response)
{
   Hexagon::Forms::Fun fun;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, fun.run());
}
