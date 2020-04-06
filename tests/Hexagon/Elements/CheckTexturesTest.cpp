
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/CheckTextures.hpp>

TEST(Hexagon_Elements_CheckTexturesTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::CheckTextures check_textures;
}

TEST(Hexagon_Elements_CheckTexturesTest, generate_grid_check__without_allegro_initialized__throws_an_error)
{
   Hexagon::Elements::CheckTextures check_textures;
   std::string expected_error_message = "[Hexagon/Elements/CheckTextures error:] cannot " \
                                        "\"generate_grid_check\" before al_init()";
   ASSERT_THROW_WITH_MESSAGE(check_textures.generate_grid_check(), std::runtime_error, expected_error_message);
}

TEST(Hexagon_Elements_CheckTexturesTest, generate_grid_check__with_a_nullptr_display__throws_an_error)
{
   al_init();
   //ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::Elements::CheckTextures check_textures(nullptr);
   std::string expected_error_message = "[Hexagon/Elements/CheckTextures error:] cannot " \
                                        "\"generate_grid_check\" with a nullptr display";
   ASSERT_THROW_WITH_MESSAGE(check_textures.generate_grid_check(), std::runtime_error, expected_error_message);

   al_uninstall_system();
}

TEST(Hexagon_Elements_CheckTexturesTest, generate_grid_check__creates_a_bitmap)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::Elements::CheckTextures check_textures(display);
   ALLEGRO_BITMAP *generated_texture = check_textures.generate_grid_check();

   ASSERT_NE(nullptr, generated_texture);

   al_uninstall_system();
}

TEST(Hexagon_Elements_CheckTexturesTest, generate_grid_check__creates_a_bitmap_with_the_expected_dimensions)
{
   al_init();
   ALLEGRO_DISPLAY *display = al_create_display(800, 600);

   Hexagon::Elements::CheckTextures check_textures(display);
   ALLEGRO_BITMAP *generated_texture = check_textures.generate_grid_check();

   ASSERT_EQ(400, al_get_bitmap_width(generated_texture));
   ASSERT_EQ(300, al_get_bitmap_height(generated_texture));

   al_uninstall_system();
}

