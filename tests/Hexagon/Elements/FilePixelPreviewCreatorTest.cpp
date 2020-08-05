
#include <gtest/gtest.h>

#include <Hexagon/Elements/FilePixelPreviewCreator.hpp>

TEST(Hexagon_Elements_FilePixelPreviewCreatorTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
}

TEST(Hexagon_Elements_FilePixelPreviewCreatorTest, create__does_not_blow_up)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
   file_pixel_preview_creator.create();
   SUCCEED();
}
