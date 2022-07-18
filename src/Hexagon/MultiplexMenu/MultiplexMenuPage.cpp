

#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MultiplexMenuPage::MultiplexMenuPage(std::vector<Hexagon::MultiplexMenu::MenuItem> items)
   : items(items)
{
}


MultiplexMenuPage::~MultiplexMenuPage()
{
}


std::vector<Hexagon::MultiplexMenu::MenuItem> &MultiplexMenuPage::get_items_ref()
{
   return items;
}


} // namespace MultiplexMenu
} // namespace Hexagon


