
#include <gtest/gtest.h>

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>

//#include <allegro5/allegro.h> // for the key names


TEST(Hexagon_MultiplexMenu_MultiplexMenuTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
}


TEST(Hexagon_MultiplexMenu_MultiplexMenuTest, set_page_dictionary__will_assign_the_page_dictionary)
{
   Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
   multiplex_menu.set_page_dictionary({
      { "foobar", Hexagon::MultiplexMenu::MultiplexMenuPage({
                Hexagon::MultiplexMenu::MenuItem("A", "Do thing"),
                Hexagon::MultiplexMenu::MenuItem("B", "Do other thing"),
                Hexagon::MultiplexMenu::MenuItem("N", "Some thing"),
            })
      },
      { "boobaz", Hexagon::MultiplexMenu::MultiplexMenuPage({
                Hexagon::MultiplexMenu::MenuItem("R", "Do r thing"),
                Hexagon::MultiplexMenu::MenuItem("N", "Other thing executes"),
                Hexagon::MultiplexMenu::MenuItem("X", "Some other thing"),
            })
      },
   });
}


TEST(Hexagon_MultiplexMenu_MultiplexMenuTest, set_page_dictionary__will_clear_the_page_history)
{
   // TODO
}


TEST(Hexagon_MultiplexMenu_MultiplexMenuTest, add_page_to_dictionary__will_add_the_page_to_the_dictionary_with_the_name)
{
   // TODO
}


TEST(Hexagon_MultiplexMenu_MultiplexMenuTest, find_page_by_name__will_return_a_page_with_the_name)
{
   // TODO
}


