
#include <gtest/gtest.h>

#include <Hexagon/MonitorInfo.hpp>


TEST(Hexagon_MonitorInfoTest, can_be_created_without_blowing_up)
{
   Hexagon::MonitorInfo monitor_info;
}


TEST(Hexagon_MonitorInfoTest, initialize__will_not_blow_up)
{
   Hexagon::MonitorInfo monitor_info;
   monitor_info.initialize();
}


