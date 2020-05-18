
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/ComponentBitmapRenderCreator.hpp>


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
   std::string expected_error_message = "ComponentBitmapRenderCreator::create_bitmap_render: error: " \
                                        "guard \"component\" not met";

   ASSERT_THROW_WITH_MESSAGE(
      component_bitmap_render_creator.create_bitmap_render(),
      std::runtime_error,
      expected_error_message
   );
}


TEST(Hexagon_ComponentBitmapRenderCreatorTest, create_bitmap_render__without_allegro_initialized_throws_an_error)
{
   Blast::Project::Component component("Foobar/Component");
   Hexagon::ComponentBitmapRenderCreator component_bitmap_render_creator(&component);

   std::string expected_error_message = "ComponentBitmapRenderCreator::create_bitmap_render: error: " \
                                        "guard \"al_is_system_installed()\" not met";

   ASSERT_THROW_WITH_MESSAGE(
      component_bitmap_render_creator.create_bitmap_render(),
      std::runtime_error,
      expected_error_message
   );
}


