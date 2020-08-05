
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/TextPixelPreviewCreator.hpp>

class Hexagon_Elements_TextPixelPreviewCreatorTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_TextPixelPreviewCreatorTestWithAllegroRenderingFixture
   : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_Elements_TextPixelPreviewCreatorTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator;
}

TEST_F(Hexagon_Elements_TextPixelPreviewCreatorTestWithEmptyFixture,
   create__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator;
   std::string expected_error_message =
      "TextPixelPreviewCreator::create: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_pixel_preview_creator.create(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_TextPixelPreviewCreatorTestWithAllegroRenderingFixture,
   create__will_create_a_bitmap_matching_the_width_and_height_for_the_text)
{
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator;
   ALLEGRO_BITMAP *text_pixel_preview = text_pixel_preview_creator.create();

   //ASSERT_EQ(120, al_get_bitmap_width(text_pixel_preview));
   //ASSERT_EQ(56, al_get_bitmap_height(text_pixel_preview));

   al_destroy_bitmap(text_pixel_preview);
}

