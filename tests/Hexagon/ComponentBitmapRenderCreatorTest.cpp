
#include <gtest/gtest.h>

#include <Hexagon/ComponentBitmapRenderCreator.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class Hexagon_ComponentBitmapRenderCreatorWithFixtureTest : public ::testing::Test
{
public:
   Hexagon_ComponentBitmapRenderCreatorWithFixtureTest() {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
   }

   virtual void TearDown() override
   {
      al_uninstall_system();
   }
};


TEST(Hexagon_ComponentBitmapRenderCreatorTest, can_be_created_without_blowing_up)
{
   Hexagon::ComponentBitmapRenderCreator component_bitmap_render_creator;
}


TEST(Hexagon_ComponentBitmapRenderCreatorTest, create_bitmap_render__without_a_component_throws_an_error)
{
   Hexagon::ComponentBitmapRenderCreator component_bitmap_render_creator(nullptr);
   ASSERT_THROW_GUARD_ERROR(
      component_bitmap_render_creator.create_bitmap_render(),
      "Hexagon::ComponentBitmapRenderCreator::create_bitmap_render",
      "component"
   );
}


TEST(Hexagon_ComponentBitmapRenderCreatorTest, create_bitmap_render__without_allegro_initialized_throws_an_error)
{
   Blast::Project::Component component("Foobar/Component");
   Hexagon::ComponentBitmapRenderCreator component_bitmap_render_creator(&component);

   ASSERT_THROW_GUARD_ERROR(
      component_bitmap_render_creator.create_bitmap_render(),
      "Hexagon::ComponentBitmapRenderCreator::create_bitmap_render",
      "al_is_system_installed()"
   );
}


