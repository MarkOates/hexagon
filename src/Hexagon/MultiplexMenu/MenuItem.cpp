

#include <Hexagon/MultiplexMenu/MenuItem.hpp>



namespace Hexagon
{
namespace MultiplexMenu
{


MenuItem::MenuItem(Hexagon::KeyboardCommandKey keyboard_command_key, std::string label, std::vector<std::string> value)
   : keyboard_command_key(keyboard_command_key)
   , label(label)
   , value(value)
{
}


MenuItem::~MenuItem()
{
}


void MenuItem::set_keyboard_command_key(Hexagon::KeyboardCommandKey keyboard_command_key)
{
   this->keyboard_command_key = keyboard_command_key;
}


void MenuItem::set_label(std::string label)
{
   this->label = label;
}


Hexagon::KeyboardCommandKey MenuItem::get_keyboard_command_key() const
{
   return keyboard_command_key;
}


std::string MenuItem::get_label() const
{
   return label;
}


std::vector<std::string> MenuItem::get_value() const
{
   return value;
}


} // namespace MultiplexMenu
} // namespace Hexagon


