
#include <gtest/gtest.h>

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

TEST_F(Hexagon_Elements_FilePixelPreviewCreatorTestWithAllegroRenderingFixture, create__does_not_blow_up)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
   file_pixel_preview_creator.create();
   SUCCEED();
}
