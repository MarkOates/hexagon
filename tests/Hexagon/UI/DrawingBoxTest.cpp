
#include <gtest/gtest.h>

#include <Hexagon/UI/DrawingBox.hpp>

TEST(Hexagon_UI_DrawingBoxTest, can_be_created_without_blowing_up)
{
   Hexagon::UI::DrawingBox drawing_box;
}

TEST(Hexagon_UI_DrawingBoxTest, run__returns_the_expected_response)
{
   Hexagon::UI::DrawingBox drawing_box;
   std::string expected_string = "Hello World!";
   //EXPECT_EQ(expected_string, drawing_box.run());
}
