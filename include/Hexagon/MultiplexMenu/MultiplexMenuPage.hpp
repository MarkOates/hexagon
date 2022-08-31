#pragma once


#include <Hexagon/KeyboardCommandKey.hpp>
#include <Hexagon/MultiplexMenu/MenuItem.hpp>
#include <vector>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MultiplexMenuPage
      {
      private:
         std::vector<Hexagon::MultiplexMenu::MenuItem> items;

      protected:


      public:
         MultiplexMenuPage(std::vector<Hexagon::MultiplexMenu::MenuItem> items={});
         ~MultiplexMenuPage();

         std::vector<Hexagon::MultiplexMenu::MenuItem> &get_items_ref();
         Hexagon::MultiplexMenu::MenuItem* find_item_by_keyboard_command_key(Hexagon::KeyboardCommandKey keyboard_command_key={});
         bool compare_keyboard_command_keys_equal(Hexagon::KeyboardCommandKey a={}, Hexagon::KeyboardCommandKey b={});
      };
   }
}



