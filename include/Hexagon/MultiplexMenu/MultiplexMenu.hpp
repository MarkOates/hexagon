#pragma once


#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>
#include <map>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MultiplexMenu
      {
      private:
         std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary;
         std::vector<std::string> page_history;

      public:
         MultiplexMenu(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary={});
         ~MultiplexMenu();

         void set_page_dictionary(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary={});
         void clear_history();
         Hexagon::MultiplexMenu::MultiplexMenuPage* current_page();
         void open_page(std::string page_name="[unset-page_name]");
         void add_page_to_dictionary(std::string page_name="[unset-page_name]", Hexagon::MultiplexMenu::MultiplexMenuPage page={});
         Hexagon::MultiplexMenu::MultiplexMenuPage* find_page_by_name(std::string page_name="[unset-page_name]");
      };
   }
}



