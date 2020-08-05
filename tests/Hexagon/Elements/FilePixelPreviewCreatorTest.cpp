
#include <gtest/gtest.h>

#include <Hexagon/Elements/FilePixelPreviewCreator.hpp>

TEST(Hexagon_Elements_FilePixelPreviewCreatorTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
}

TEST(Hexagon_Elements_FilePixelPreviewCreatorTest, run__returns_the_expected_response)
{
   Hexagon::Elements::FilePixelPreviewCreator file_pixel_preview_creator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, file_pixel_preview_creator.run());
}
