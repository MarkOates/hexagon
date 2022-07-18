

#include <Hexagon/MultiplexMenu/MenuItem.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MenuItem::MenuItem(std::string keyboard_key_to_activate, std::string label, std::string value)
   : keyboard_key_to_activate(keyboard_key_to_activate)
   , label(label)
   , value(value)
{
}


MenuItem::~MenuItem()
{
}


void MenuItem::set_keyboard_key_to_activate(std::string keyboard_key_to_activate)
{
   this->keyboard_key_to_activate = keyboard_key_to_activate;
}


void MenuItem::set_label(std::string label)
{
   this->label = label;
}


std::string MenuItem::get_keyboard_key_to_activate()
{
   return keyboard_key_to_activate;
}


std::string MenuItem::get_label()
{
   return label;
}


std::string MenuItem::get_value()
{
   return value;
}


} // namespace MultiplexMenu
} // namespace Hexagon


