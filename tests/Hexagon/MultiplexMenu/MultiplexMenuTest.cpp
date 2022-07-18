
#include <gtest/gtest.h>

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>

#include <allegro5/allegro.h> // for the key names


class Hexagon_MultiplexMenu_MultiplexMenuTest : public ::testing::Test
{};

class Hexagon_MultiplexMenu_MultiplexMenuWithFixturesTest : public ::testing::Test
{
protected:
   Hexagon::MultiplexMenu::MultiplexMenuPage build_menu_page_a()
   {
      return Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_A, true}, "Do thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_B},       "Do other thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_N},       "Some thing"),
      });
   }
   Hexagon::MultiplexMenu::MultiplexMenuPage build_menu_page_b()
   {
      return Hexagon::MultiplexMenu::MultiplexMenuPage({
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_R}, "Do R thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_N}, "Other thing executes"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_X}, "Some other thing"),
         Hexagon::MultiplexMenu::MenuItem({ALLEGRO_KEY_Z}, "Something else"),
      });
   }
   std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> build_dictionary_a()
   {
      return {
         { "page_a", build_menu_page_a() },
         { "page_b", build_menu_page_b() },
      };
   }
};


TEST_F(Hexagon_MultiplexMenu_MultiplexMenuTest, can_be_created_without_blowing_up)
{
   Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
}


TEST_F(Hexagon_MultiplexMenu_MultiplexMenuWithFixturesTest, set_page_dictionary__will_assign_the_page_dictionary)
{
   Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu;
   std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary = build_dictionary_a();
   
   multiplex_menu.set_page_dictionary(page_dictionary);

   //EXPECT_EQ(page_dictionary, page_dictionary);
   //TODO finish this test
}


TEST_F(Hexagon_MultiplexMenu_MultiplexMenuWithFixturesTest, set_page_dictionary__will_clear_the_page_history)
{
   // TODO
}


TEST_F(Hexagon_MultiplexMenu_MultiplexMenuWithFixturesTest, find_page_by_name__will_return_a_page_with_the_name)
{
   Hexagon::MultiplexMenu::MultiplexMenu multiplex_menu(build_dictionary_a());

   Hexagon::MultiplexMenu::MultiplexMenuPage *page = nullptr;
   page = multiplex_menu.find_page_by_name("page_b");
   ASSERT_NE(nullptr, page);
   // TODO
}


