

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenu::MultiplexMenu(std::vector<Hexagon::MultiplexMenu::MenuItem> items)
   : items(items)
{
}


MultiplexMenu::~MultiplexMenu()
{
}


std::vector<Hexagon::MultiplexMenu::MenuItem> &MultiplexMenu::get_items_ref()
{
   return items;
}


} // namespace MultiplexMenu
} // namespace Hexagon


