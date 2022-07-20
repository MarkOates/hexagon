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
         std::vector<Hexagon::MultiplexMenu::MultiplexMenuPage*> page_history;
         std::vector<std::string> final_command_set_to_execute;

      public:
         MultiplexMenu(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary={});
         ~MultiplexMenu();

         void set_final_command_set_to_execute(std::vector<std::string> final_command_set_to_execute);
         std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> get_page_dictionary();
         std::vector<Hexagon::MultiplexMenu::MultiplexMenuPage*> get_page_history();
         std::vector<std::string> get_final_command_set_to_execute();
         void set_page_dictionary(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary={});
         int get_num_pages();
         void clear_history();
         Hexagon::MultiplexMenu::MultiplexMenuPage* infer_current_page();
         void open_page(std::string page_name="[unset-page_name]");
         Hexagon::MultiplexMenu::MultiplexMenuPage* find_page_by_name(std::string page_name="[unset-page_name]");
      };
   }
}



