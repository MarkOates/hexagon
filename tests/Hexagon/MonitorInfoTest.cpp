
#include <gtest/gtest.h>

#include <Hexagon/MonitorInfo.hpp>
#include <allegro5/allegro.h>


TEST(Hexagon_MonitorInfoTest, can_be_created_without_blowing_up)
{
   Hexagon::MonitorInfo monitor_info;
}


TEST(Hexagon_MonitorInfoTest, initialize__will_not_blow_up)
{
   al_init();
   Hexagon::MonitorInfo monitor_info;
   monitor_info.initialize();
   al_uninstall_system();
}


TEST(Hexagon_MonitorInfoTest, initialize__will_assign_the_monitors)
{
   al_init();
   Hexagon::MonitorInfo monitor_info;
   monitor_info.initialize();

   EXPECT_EQ(1, monitor_info.get_num_monitors());

   al_uninstall_system();
}


