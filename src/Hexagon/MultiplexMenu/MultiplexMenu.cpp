

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenu::MultiplexMenu(std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> pages)
   : pages(pages)
{
}


MultiplexMenu::~MultiplexMenu()
{
}


std::map<std::string, Hexagon::MultiplexMenu::MultiplexMenuPage> &MultiplexMenu::get_pages_ref()
{
   return pages;
}


} // namespace MultiplexMenu
} // namespace Hexagon


