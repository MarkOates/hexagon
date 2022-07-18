#pragma once


#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>
#include <map>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MultiplexMenu
      {
      private:
         std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> pages;

      public:
         MultiplexMenu(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> pages={});
         ~MultiplexMenu();

         std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> &get_pages_ref();
      };
   }
}



