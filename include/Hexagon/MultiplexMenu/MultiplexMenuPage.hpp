#pragma once


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

      public:
         MultiplexMenuPage(std::vector<Hexagon::MultiplexMenu::MenuItem> items={});
         ~MultiplexMenuPage();

         std::vector<Hexagon::MultiplexMenu::MenuItem> &get_items_ref();
      };
   }
}



