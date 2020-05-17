
#include <gtest/gtest.h>

#include <Hexagon/AdvancedComponentNavigator/Renderer.hpp>

TEST(Hexagon_AdvancedComponentNavigator_RendererTest, can_be_created_without_blowing_up)
{
   Hexagon::AdvancedComponentNavigator::Renderer renderer;
}

TEST(Hexagon_AdvancedComponentNavigator_RendererTest, render__can_be_called_without_crashing)
{
   Hexagon::AdvancedComponentNavigator::Renderer renderer;
   renderer.render();
   SUCCEED();
}
