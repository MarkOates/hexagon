
#include <gtest/gtest.h>

#include <Hexagon/Elements/TextGrid.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

#include <allegro5/allegro.h>
#include<allegro_flare/placement3d.h> // for placement3d

class Hexagon_Elements_TextGridTest_WithEmptyFixture : public ::testing::Test
{
public:
   Hexagon_Elements_TextGridTest_WithEmptyFixture() {}
};

class Hexagon_Elements_TextGridTest_WithAllegroRenderingFixture : public ::testing::Test
{
public:
   ALLEGRO_DISPLAY* display;

public:
   Hexagon_Elements_TextGridTest_WithAllegroRenderingFixture()
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

ALLEGRO_COLOR w = {1.0f, 1.0f, 1.0f, 1.0f};
ALLEGRO_COLOR r = {1.0f, 0.0f, 0.0f, 1.0f};
ALLEGRO_COLOR t = {0.0f, 1.0f, 1.0f, 1.0f};
ALLEGRO_COLOR _ = {0.0f, 0.0f, 0.0f, 0.0f};
std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> BASIC_GRID_FIXTURE = {
   { { 'H', w, _ }, { 'e', w, _ }, { 'l', w, _ }, { 'l', w, _ }, { 'o', w, _ }, },
   { { 'G', w, _ }, { 'r', w, _ }, { 'i', w, _ }, { 'd', w, _ }, { '!', w, _ }, },
};

std::vector<std::vector<std::tuple<char, ALLEGRO_COLOR, ALLEGRO_COLOR>>> COLORED_GRID_FIXTURE = {
   { { 'H', w, _ }, { 'e', w, r }, { 'l', w, _ }, { 'l', t, r }, { 'o', t, _ }, },
   { { 'C', w, r }, { 'o', w, _ }, { 'l', w, r }, { 'o', t, _ }, { 'r', t, r }, { '!', w, _ }, },
};

TEST_F(Hexagon_Elements_TextGridTest_WithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextGrid text_grid;
}

TEST_F(Hexagon_Elements_TextGridTest_WithEmptyFixture, render__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::TextGrid text_grid;
   EXPECT_THROW_GUARD_ERROR(
      text_grid.render(),
      "Hexagon::Elements::TextGrid::render",
      "al_is_system_installed()"
   );
}

//TEST_F(Hexagon_Elements_TextGridTest_WithEmptyFixture,
//   render__without_primitives_initialized__raises_an_error)
//{
//   Hexagon::Elements::TextGrid text_grid;
//   std::string expected_error_message =
//      "TextGrid::render: error: guard "al_is_primitives_addon_initialized()" not met";
//   ASSERT_THROW_WITH_MESSAGE(text_grid.render(), std::runtime_error, expected_error_message);
//}

TEST_F(Hexagon_Elements_TextGridTest_WithAllegroRenderingFixture, render__without_a_font__raises_an_error)
{
   Hexagon::Elements::TextGrid text_grid;
   EXPECT_THROW_GUARD_ERROR(
      text_grid.render(),
      "Hexagon::Elements::TextGrid::render",
      "font"
   );
}

TEST_F(Hexagon_Elements_TextGridTest_WithAllegroRenderingFixture,
   render__with_the_valid_arguments__does_not_blow_up)
{
   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   ALLEGRO_FONT *font = al_create_builtin_font();
   int cell_width = al_get_text_width(font, " ");
   int cell_height = al_get_font_line_height(font);
   place.size = vec3d(600, 300, 0);
   Hexagon::Elements::TextGrid text_grid(font, cell_width, cell_height, 0, 0, BASIC_GRID_FIXTURE);

   al_clear_to_color({0.0f, 0.0f, 0.0f, 0.0f});
   place.start_transform();
   text_grid.render();
   place.restore_transform();
   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_TextGridTest_WithAllegroRenderingFixture,
   render__renders_foreground_and_background_colors)
{
   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   ALLEGRO_FONT *font = al_create_builtin_font();
   int cell_width = al_get_text_width(font, " ");
   int cell_height = al_get_font_line_height(font);
   place.size = vec3d(600, 300, 0);
   Hexagon::Elements::TextGrid text_grid(font, cell_width, cell_height, 0, 0, COLORED_GRID_FIXTURE);

   al_clear_to_color({0.0f, 0.0f, 0.0f, 0.0f});
   place.start_transform();
   text_grid.render();
   place.restore_transform();
   al_flip_display();

   //sleep(1);
}

TEST_F(Hexagon_Elements_TextGridTest_WithAllegroRenderingFixture,
   render__renders_cells_with_spacing)
{
   placement3d place(al_get_display_width(display)/2, al_get_display_height(display)/2, 0);
   ALLEGRO_FONT *font = al_create_builtin_font();
   int cell_width = al_get_text_width(font, " ");
   int cell_height = al_get_font_line_height(font);
   place.size = vec3d(600, 300, 0);
   Hexagon::Elements::TextGrid text_grid(font, cell_width, cell_height, 6, 12, COLORED_GRID_FIXTURE);

   al_clear_to_color({0.0f, 0.0f, 0.0f, 0.0f});
   place.start_transform();
   text_grid.render();
   place.restore_transform();
   al_flip_display();

   //sleep(1);
}

