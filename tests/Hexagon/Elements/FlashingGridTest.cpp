
#include <gtest/gtest.h>

#include <Hexagon/Elements/FlashingGrid.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro.h>
#include<allegro_flare/placement3d.h> // for placement3d

class Hexagon_Elements_FlashingGridTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_FlashingGridTest_WithEmptyFixture() {}
};

class Hexagon_Elements_FlashingGridTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;

public:
   Hexagon_Elements_FlashingGridTest_WithAllegroRenderingFixture()
      : display(nullptr)
   {}

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
      display = al_create_display(1280, 720);
   }

   virtual void TearDown() override
   {
      al_destroy_display(display);
      al_uninstall_system();
   }
};

TEST_F(Hexagon_Elements_FlashingGridTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FlashingGrid flashing_grid;
}

TEST_F(Hexagon_Elements_FlashingGridTest_WithEmptyFixture, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::FlashingGrid flashing_grid;
   //std::string expected_error_message = "FlashingGrid::render: error: guard \"al_is_system_installed()\" not met";
   //ASSERT_THROW_WITH_MESSAGE(flashing_grid.render(), std::runtime_error, expected_error_message);
   ASSERT_THROW_GUARD_ERROR(
      flashing_grid.render(),
      "Hexagon::Elements::FlashingGrid::render",
      "al_is_system_installed()"
   );
}

//TEST_F(Hexagon_Elements_FlashingGridTest_WithEmptyFixture,
//   render__without_primitives_initialized__raises_an_error)
//{
//   Hexagon::Elements::FlashingGrid flashing_grid;
//   std::string expected_error_message =
//      "FlashingGrid::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
//   ASSERT_THROW_WITH_MESSAGE(flashing_grid.render(), std::runtime_error, expected_error_message);
//}

TEST_F(Hexagon_Elements_FlashingGridTest_WithAllegroRenderingFixture,
   render__with_the_valid_arguments__does_not_blow_up)
{
   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   place.size = vec3d(600, 300, 0);
   Hexagon::Elements::FlashingGrid flashing_grid(place.size.x, place.size.y);

   for (unsigned i=0; i<60; i++)
   {
      flashing_grid.set_counter(i);

      al_clear_to_color({0.0f, 0.0f, 0.0f, 0.0f});
      place.start_transform();
      flashing_grid.render();
      place.restore_transform();
      al_flip_display();
   }
}
