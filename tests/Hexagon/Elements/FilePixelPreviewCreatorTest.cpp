
#include <gtest/gtest.h>

#include <Hexagon/Elements/FilePixelPreviewCreator.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>

// TODO: Use a more proper fixture file
std::string FIXTURE_FILE = "/Users/markoates/Repos/hexagon/tests/Hexagon/Elements/FilePixelPreviewCreatorTest.cpp";

class Hexagon_Elements_FilePixelPreviewCreatorTestWithEmptyFixture : public ::testing::Test
{};

#include <Testing/WithAllegroRenderingFixture.hpp>

class Hexagon_Elements_FilePixelPreviewCreatorTestWithAllegroRenderingFixture
   : public Testing::WithAllegroRenderingFixture
{};

TEST_F(Hexagon_Elements_FilePixelPreviewCreatorTestWithEmptyFixture, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
}

TEST_F(Hexagon_Elements_FilePixelPreviewCreatorTestWithEmptyFixture,
   create__without_allegro_initialized__raises_an_error)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
   EXPECT_THROW_GUARD_ERROR(
      file_pixel_preview_creator.create(),
      "Hexagon::Elements::FilePixelPreviewCreator::create",
      "al_is_system_installed()"
   );
}

TEST_F(Hexagon_Elements_FilePixelPreviewCreatorTestWithAllegroRenderingFixture,
   create__for_a_file_that_does_not_exist__raises_an_exception)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator("/a_file/that/does_not_exist");
   std::string expected_error_message =
      "FilePixelPreviewCreator::create: error: the file \"/a_file/that/does_not_exist\" does not exist.";
   EXPECT_THROW_WITH_MESSAGE(file_pixel_preview_creator.create(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_FilePixelPreviewCreatorTestWithAllegroRenderingFixture,
   create__will_create_a_bitmap_matching_the_width_and_height_for_the_file)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator(FIXTURE_FILE);
   ALLEGRO_BITMAP *file_pixel_preview = file_pixel_preview_creator.create();

   ASSERT_EQ(120, al_get_bitmap_width(file_pixel_preview));
   ASSERT_EQ(112, al_get_bitmap_height(file_pixel_preview));

   al_destroy_bitmap(file_pixel_preview);
}

