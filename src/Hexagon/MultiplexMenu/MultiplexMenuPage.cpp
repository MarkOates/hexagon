

#include <Hexagon/MultiplexMenu/MultiplexMenuPage.hpp>

#include <Hexagon/KeyboardCommandKey.hpp>


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


Hexagon::MultiplexMenu::MenuItem* MultiplexMenuPage::find_item_by_keyboard_command_key(Hexagon::KeyboardCommandKey keyboard_command_key)
{
   for (auto &menu_item : items)
   {
      if (compare_keyboard_command_keys_equal(keyboard_command_key, menu_item.get_keyboard_command_key()))
         return &menu_item;
   }
   return nullptr;
}

bool MultiplexMenuPage::compare_keyboard_command_keys_equal(Hexagon::KeyboardCommandKey a, Hexagon::KeyboardCommandKey b)
{
   if (a.get_al_keycode() != b.get_al_keycode()) return false;
   if (a.get_shift() != b.get_shift()) return false;
   if (a.get_alt() != b.get_alt()) return false;
   if (a.get_command() != b.get_command()) return false;
   if (a.get_ctrl() != b.get_ctrl()) return false;
   return true;
}


} // namespace MultiplexMenu
} // namespace Hexagon


