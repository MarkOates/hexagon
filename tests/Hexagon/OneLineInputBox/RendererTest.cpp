
#include <gtest/gtest.h>

#include <Hexagon/OneLineInputBox/Renderer.hpp>

TEST(Hexagon_OneLineInputBox_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::OneLineInputBox::Renderer renderer;
}

TEST(Hexagon_OneLineInputBox_RendererTest, render__renders_the_box)
{
   Hexagon::OneLineInputBox::Renderer renderer;
   renderer.render();
   SUCCEED();
}
