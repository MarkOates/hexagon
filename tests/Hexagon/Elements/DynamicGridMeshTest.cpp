
#include <gtest/gtest.h>

#include <Hexagon/Elements/DynamicGridMesh.hpp>

#include <allegro5/allegro_color.h>

class Hexagon_Elements_DynamicGridMeshTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_DynamicGridMeshTest_WithEmptyFixture() {}
};

class Hexagon_Elements_DynamicGridMeshTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;
   ALLEGRO_BITMAP* multi_colored_bitmap_fixture;

public:
   Hexagon_Elements_DynamicGridMeshTest_WithAllegroRenderingFixture()
      : display(nullptr)
      , multi_colored_bitmap_fixture(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      ASSERT_EQ(true, al_init_primitives_addon());
      display = al_create_display(16 * 256, 9 * 256);
   }

   virtual void TearDown() override
   {
      if (multi_colored_bitmap_fixture) al_destroy_bitmap(multi_colored_bitmap_fixture);
      al_destroy_display(display);
      al_uninstall_system();
   }

   ALLEGRO_BITMAP* get_or_build_multi_colored_bitmap_fixture()
   {
      if (multi_colored_bitmap_fixture) return multi_colored_bitmap_fixture;

      multi_colored_bitmap_fixture = al_create_bitmap(30, 30);
      al_set_target_bitmap(multi_colored_bitmap_fixture);
      al_clear_to_color({1.0f, 1.0f, 1.0f, 1.0f});

      al_draw_filled_rectangle(0, 0, 10, 10, al_color_name("pink"));
      al_draw_filled_rectangle(10, 0, 20, 10, al_color_name("orange"));
      al_draw_filled_rectangle(20, 0, 30, 10, al_color_name("blue"));

      al_draw_filled_rectangle(0, 10, 10, 20, al_color_name("yellow"));
      al_draw_filled_rectangle(10, 10, 20, 20, al_color_name("green"));
      al_draw_filled_rectangle(20, 10, 30, 20, al_color_name("red"));

      al_draw_filled_rectangle(0, 20, 10, 30, al_color_name("black"));
      al_draw_filled_rectangle(10, 20, 20, 30, al_color_name("gray"));
      al_draw_filled_rectangle(20, 20, 30, 30, al_color_name("white"));

      // restore previous state
      al_set_target_bitmap(al_get_backbuffer(display));

      return multi_colored_bitmap_fixture;
   }
};


TEST_F(Hexagon_Elements_DynamicGridMeshTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
}


TEST_F(Hexagon_Elements_DynamicGridMeshTest_WithAllegroRenderingFixture, render__draws_the_mesh)
{
   // TODO
   //al_clear_to_color(al_color_name("saddlebrown"));
   //al_flip_display();
   //sleep(2);
}


