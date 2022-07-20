

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenu::MultiplexMenu(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary)
   : page_dictionary(page_dictionary)
   , page_history({})
   , final_command_set_to_execute({"[command_to_execute-not-set]"})
{
}


MultiplexMenu::~MultiplexMenu()
{
}


void MultiplexMenu::set_final_command_set_to_execute(std::vector<std::string> final_command_set_to_execute)
{
   this->final_command_set_to_execute = final_command_set_to_execute;
}


std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> MultiplexMenu::get_page_dictionary()
{
   return page_dictionary;
}


std::vector<Hexagon::MultiplexMenu::MultiplexMenuPage*> MultiplexMenu::get_page_history()
{
   return page_history;
}


std::vector<std::string> MultiplexMenu::get_final_command_set_to_execute()
{
   return final_command_set_to_execute;
}


void MultiplexMenu::set_page_dictionary(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary)
{
   this->page_dictionary = page_dictionary;
   clear_history();
   return;
}

int MultiplexMenu::get_num_pages()
{
   return page_history.size();
}

void MultiplexMenu::clear_history()
{
   page_history.clear();
   return;
}

Hexagon::MultiplexMenu::MultiplexMenuPage* MultiplexMenu::infer_current_page()
{
   if (page_history.empty()) return nullptr;
   return page_history.back();
}

void MultiplexMenu::open_page(std::string page_name)
{
   page_history.push_back(find_page_by_name(page_name));
   return;
     
}

Hexagon::MultiplexMenu::MultiplexMenuPage* MultiplexMenu::find_page_by_name(std::string page_name)
{
   std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage>::iterator it;
   it = page_dictionary.find(page_name);
   if (it != page_dictionary.end()) return &it->second;
   return nullptr;
}
} // namespace MultiplexMenu
} // namespace Hexagon


