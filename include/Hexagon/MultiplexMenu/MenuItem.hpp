#pragma once


#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MenuItem
      {
      private:
         std::string keyboard_key_to_activate;
         std::string label;
         std::string value;

      public:
         MenuItem(std::string keyboard_key_to_activate="[menu-item-key_to_activate-not-set]", std::string label="[menu-item-label-not-set]", std::string value="[menu-item-value-not-set]");
         ~MenuItem();

         void set_keyboard_key_to_activate(std::string keyboard_key_to_activate);
         void set_label(std::string label);
         std::string get_keyboard_key_to_activate();
         std::string get_label();
         std::string get_value();
      };
   }
}



