

#include <Hexagon/MultiplexMenu/MenuItem.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MenuItem::MenuItem(std::string keyboard_input, std::string label, std::string action, std::string menu)
   : keyboard_input(keyboard_input)
   , label(label)
   , action(action)
   , menu(menu)
{
}


MenuItem::~MenuItem()
{
}


void MenuItem::set_keyboard_input(std::string keyboard_input)
{
   this->keyboard_input = keyboard_input;
}


void MenuItem::set_label(std::string label)
{
   this->label = label;
}


void MenuItem::set_action(std::string action)
{
   this->action = action;
}


void MenuItem::set_menu(std::string menu)
{
   this->menu = menu;
}


std::string MenuItem::get_keyboard_input()
{
   return keyboard_input;
}


std::string MenuItem::get_label()
{
   return label;
}


std::string MenuItem::get_action()
{
   return action;
}


std::string MenuItem::get_menu()
{
   return menu;
}


} // namespace MultiplexMenu
} // namespace Hexagon


