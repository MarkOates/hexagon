
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/TextMesh.hpp>

#include <allegro5/allegro_color.h>

TEST(Hexagon_Elements_TextMeshTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextMesh text_mesh;
}

TEST(Hexagon_Elements_TextMeshTest, initialize__without_a_valid_font__will_raise_an_error)
{
   Hexagon::Elements::TextMesh text_mesh(nullptr);
   std::string expected_error_message = "TextMesh::initialize: error: guard \"font\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_mesh.initialize(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Elements_TextMeshTest, initialize__will_create_the_font_character_bitmap)
{
   al_init();
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();

   Hexagon::Elements::TextMesh text_mesh(a_valid_font);
   text_mesh.initialize();
   ASSERT_NE(nullptr, text_mesh.get_font_character_map_bitmap());

   al_destroy_font(a_valid_font);
   al_uninstall_system();
}

TEST(Hexagon_Elements_TextMeshTest, initialize__will_set_the_cell_width_and_the_cell_height_to_match_the_font)
{
   al_init();
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();

   Hexagon::Elements::TextMesh text_mesh(a_valid_font);
   text_mesh.initialize();
   EXPECT_EQ(8, text_mesh.get_cell_width());
   EXPECT_EQ(8, text_mesh.get_cell_height());

   al_destroy_font(a_valid_font);
   al_uninstall_system();
}

TEST(Hexagon_Elements_TextMeshTest, render__without_having_initialized__will_raise_an_error)
{
   al_init();
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();

   Hexagon::Elements::TextMesh text_mesh(a_valid_font);
   std::string expected_error_message = "TextMesh::render: error: guard \"initialized\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_mesh.render(), std::runtime_error, expected_error_message);

   al_destroy_font(a_valid_font);
   al_uninstall_system();
}

TEST(Hexagon_Elements_TextMeshTest, render__will_draw_the_mesh)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1280, 720);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();
   Hexagon::Elements::TextMesh text_mesh(a_valid_font);

   text_mesh.initialize();

   text_mesh.render();
   al_flip_display();

   al_destroy_font(a_valid_font);
   al_uninstall_system();
}

TEST(Hexagon_Elements_TextMeshTest, set_cell_background_color__will_set_the_background_color_of_the_cell)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1280, 720);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();

   Hexagon::Elements::TextMesh text_mesh(a_valid_font, 30, 20);

   text_mesh.initialize();

   for (unsigned y=0; y<text_mesh.get_num_rows(); y++)
   {
      for (unsigned x=0; x<text_mesh.get_num_columns(); x++)
      {
         text_mesh.set_cell_background_color(x, y, al_color_name("red"));
         text_mesh.set_cell_character(x, y, '*');
      }
   }

   text_mesh.render();
   al_flip_display();

   sleep(1);

   al_destroy_font(a_valid_font);
   al_uninstall_system();
}

