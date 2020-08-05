
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <Hexagon/Elements/FilePixelPreviewCreator.hpp>

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
   std::string expected_error_message =
      "FilePixelPreviewCreator::create: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(file_pixel_preview_creator.create(), std::runtime_error, expected_error_message);
}

TEST_F(Hexagon_Elements_FilePixelPreviewCreatorTestWithAllegroRenderingFixture, create__does_not_blow_up)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
   file_pixel_preview_creator.create();
   SUCCEED();
}
