
#include <gtest/gtest.h>

#include <Hexagon/Elements/Window.hpp>

TEST(Hexagon_Elements_WindowTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Window window;
}

TEST(Hexagon_Elements_WindowTest, run__returns_the_expected_response)
{
   Hexagon::Elements::Window window;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, window.run());
}
