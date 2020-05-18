
#include <gtest/gtest.h>

#include <Hexagon/ComponentBitmapRenderCreator.hpp>


class Hexagon_ComponentBitmapRenderCreatorTest : public ::testing::Test
{
public:
   Hexagon_ComponentBitmapRenderCreatorTest() {}
   virtual void SetUp() override {}
   virtual void TearDown() override {}
};


TEST_F(Hexagon_ComponentBitmapRenderCreatorTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentBitmapRenderCreator component_bitmap_render_creator;
}


