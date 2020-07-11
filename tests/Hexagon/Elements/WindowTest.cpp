
#include <gtest/gtest.h>

#include <Hexagon/Elements/Window.hpp>

TEST(Hexagon_Elements_WindowTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::Window window;
}

TEST(Hexagon_Elements_WindowTest, draw__does_not_blow_up)
{
   Hexagon::Elements::Window window;
   window.draw();
   SUCCEED();
}
