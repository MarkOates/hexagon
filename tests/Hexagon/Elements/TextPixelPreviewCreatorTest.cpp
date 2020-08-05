
#include <gtest/gtest.h>

#include <Hexagon/Elements/TextPixelPreviewCreator.hpp>

TEST(Hexagon_Elements_TextPixelPreviewCreatorTest, can_be_created_without_blowing_up)
{
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator;
}

TEST(Hexagon_Elements_TextPixelPreviewCreatorTest, run__returns_the_expected_response)
{
   Hexagon::Elements::TextPixelPreviewCreator text_pixel_preview_creator;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, text_pixel_preview_creator.run());
}
