
#include <gtest/gtest.h>

#include <Hexagon/Monitor.hpp>


TEST(Hexagon_MonitorTest, can_be_created_without_blowing_up)
{
   Hexagon::Monitor monitor;
}


TEST(Hexagon_MonitorTest, infer_width_inches__will_return_the_estimated_physical_width_of_the_monitor)
{
   Hexagon::Monitor monitor;
   monitor.set_desktop_x2(3600);
   monitor.set_dpi(300);

   EXPECT_FLOAT_EQ(12.0, monitor.infer_width_inches());
}


TEST(Hexagon_MonitorTest, infer_height_inches__will_return_the_estimated_physical_height_of_the_monitor)
{
   Hexagon::Monitor monitor;
   monitor.set_desktop_y2(2700);
   monitor.set_dpi(300);

   EXPECT_FLOAT_EQ(9.0, monitor.infer_height_inches());
}


