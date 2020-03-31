
#include <gtest/gtest.h>

#include <Hexgaon/Powerbar/Powerbar.hpp>

TEST(Hexgaon_Powerbar_PowerbarTest, can_be_created_without_blowing_up)
{
   Hexgaon::Powerbar::Powerbar powerbar;
}

TEST(Hexgaon_Powerbar_PowerbarTest, run__returns_the_expected_response)
{
   Hexgaon::Powerbar::Powerbar powerbar;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, powerbar.run());
}
