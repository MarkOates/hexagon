#pragma once


#include <Hexagon/MultiplexMenu/MenuItem.hpp>
#include <vector>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MultiplexMenu
      {
      private:
         std::vector<Hexagon::MultiplexMenu::MenuItem> items;

      public:
         MultiplexMenu(std::vector<Hexagon::MultiplexMenu::MenuItem> items={});
         ~MultiplexMenu();

         std::vector<Hexagon::MultiplexMenu::MenuItem> &get_items_ref();
      };
   }
}



