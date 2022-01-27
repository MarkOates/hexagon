

#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenu::MultiplexMenu(std::vector<std::tuple<std::string, std::string, std::string, std::string>> items)
   : items(items)
{
}


MultiplexMenu::~MultiplexMenu()
{
}


std::vector<std::tuple<std::string, std::string, std::string, std::string>> &MultiplexMenu::get_items_ref()
{
   return items;
}


} // namespace MultiplexMenu
} // namespace Hexagon


