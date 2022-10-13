
#include <gtest/gtest.h>

#include <Hexagon/DarkModeDetector.hpp>


TEST(Hexagon_DarkModeDetectorTest, can_be_created_without_blowing_up)
{
   Hexagon::DarkModeDetector dark_mode_detector;
}


TEST(Hexagon_DarkModeDetectorTest, DISABLED__is_light__returns_true_if_the_os_is_not_in_dark_mode)
   // DISABLED because it relies on the state of the OS which is unpredictable
{
   Hexagon::DarkModeDetector dark_mode_detector;
   EXPECT_EQ(false, dark_mode_detector.is_light());
}


TEST(Hexagon_DarkModeDetectorTest, DISABLED__is_dark__returns_the_expected_response)
   // DISABLED because it relies on the state of the OS which is unpredictable
{
   Hexagon::DarkModeDetector dark_mode_detector;
   EXPECT_EQ(true, dark_mode_detector.is_dark());
}


