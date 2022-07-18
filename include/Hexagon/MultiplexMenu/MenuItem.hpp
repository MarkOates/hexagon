#pragma once


#include <Hexagon/KeyboardCommandKey.hpp>
#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MenuItem
      {
      private:
         Hexagon::KeyboardCommandKey keyboard_command_key;
         std::string label;
         std::string value;

      public:
         MenuItem(Hexagon::KeyboardCommandKey keyboard_command_key={}, std::string label="[menu-item-label-not-set]", std::string value="[menu-item-value-not-set]");
         ~MenuItem();

         void set_keyboard_command_key(Hexagon::KeyboardCommandKey keyboard_command_key);
         void set_label(std::string label);
         Hexagon::KeyboardCommandKey get_keyboard_command_key();
         std::string get_label();
         std::string get_value();
      };
   }
}



