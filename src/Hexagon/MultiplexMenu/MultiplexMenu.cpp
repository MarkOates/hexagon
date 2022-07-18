

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenu::MultiplexMenu(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary)
   : page_dictionary(page_dictionary)
   , page_history({"start"})
{
}


MultiplexMenu::~MultiplexMenu()
{
}


void MultiplexMenu::set_page_dictionary(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> page_dictionary)
{
   this->page_dictionary = page_dictionary;
   clear_history();
   return;
}

void MultiplexMenu::clear_history()
{
   page_history.clear();
   return;
}

Hexagon::MultiplexMenu::MultiplexMenuPage* MultiplexMenu::current_page()
{
   if (page_history.empty()) return nullptr;
   return find_page_by_name(page_history.back());
}

void MultiplexMenu::open_page(std::string page_name)
{
   return;
     
}

void MultiplexMenu::add_page_to_dictionary(std::string page_name, Hexagon::MultiplexMenu::MultiplexMenuPage page)
{
   // cannot already exist
   return;
}

Hexagon::MultiplexMenu::MultiplexMenuPage* MultiplexMenu::find_page_by_name(std::string page_name)
{
   std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage>::iterator it;
   it = page_dictionary.find(page_name);
   if (it != page_dictionary.end())
   return &it->second;
}
} // namespace MultiplexMenu
} // namespace Hexagon


