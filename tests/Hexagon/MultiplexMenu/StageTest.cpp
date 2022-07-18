
#include <gtest/gtest.h>

#include <Hexagon/MultiplexMenu/Stage.hpp>


TEST(Hexagon_MultiplexMenu_StageTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::Stage multiplex_menu;
}


TEST(Hexagon_MultiplexMenu_StageTest, process_local_event__does_not_blow_up)
{
   Hexagon::MultiplexMenu::Stage multiplex_menu;
   multiplex_menu.process_local_event();
   SUCCEED();
}


TEST(Hexagon_MultiplexMenu_StageTest, process_event__does_not_blow_up)
{
   Hexagon::MultiplexMenu::Stage multiplex_menu;
   multiplex_menu.process_event();
   SUCCEED();
}


