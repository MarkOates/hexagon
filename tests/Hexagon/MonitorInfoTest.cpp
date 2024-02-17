
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


TEST(Hexagon_MonitorInfoTest, initialize__will_assign_the_monitors_with_the_expected_info)
{
   al_init();
   Hexagon::MonitorInfo monitor_info;
   monitor_info.initialize();

   EXPECT_EQ(1, monitor_info.get_num_monitors());

   // Known monitors:
   // LG monitor
   // 13" laptop screen
   // 16" laptop screen
   // DELL monitor screen

   al_uninstall_system();
}


TEST(Hexagon_MonitorInfoTest, get_primary_monitor_info__will_return_the_monitor_info_of_the_primary_monitor)
{
   al_init();
   Hexagon::MonitorInfo monitor_info;
   monitor_info.initialize();

   Hexagon::Monitor primary_monitor = monitor_info.get_primary_monitor_info();
   EXPECT_EQ(0, primary_monitor.get_desktop_x1());
   EXPECT_EQ(0, primary_monitor.get_desktop_y1());

   // Known monitors:
   // LG monitor
   // 13" laptop screen
   // 16" laptop screen
   // DELL monitor screen

   al_uninstall_system();
}


TEST(Hexagon_MonitorInfoTest, DISABLED__dump_monitor_info__will_output_the_monitor_info_as_a_string)
{
   //al_init();
   //Hexagon::MonitorInfo monitor_info;
   //monitor_info.initialize();

   //std::cout << monitor_info.dump_monitor_info() << std::endl;

   //al_uninstall_system();
}


