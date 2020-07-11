
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

TEST(Hexagon_Elements_TextMeshTest, render__will_draw_the_mesh__with_the_generated_font_character_map_bitmap)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(1280, 720);
   al_clear_to_color(al_color_name("black"));
   ALLEGRO_FONT *a_valid_font = al_create_builtin_font();
   Hexagon::Elements::TextMesh text_mesh(a_valid_font, 20, 30);

   text_mesh.initialize();

   text_mesh.set_cell_background_color(1, 1, al_color_name("red"));
   text_mesh.set_cell_character(0, 0, 'A');

   text_mesh.render();
   al_flip_display();

   sleep(2);

   al_destroy_font(a_valid_font);
   al_uninstall_system();
}

