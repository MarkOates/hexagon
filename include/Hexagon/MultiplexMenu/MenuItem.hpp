#pragma once


#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MenuItem
      {
      private:
         std::string keyboard_input;
         std::string label;
         std::string action;
         std::string menu;

      public:
         MenuItem(std::string keyboard_input="[keyboard-input-not-set]", std::string label="[menu-item-label-not-set]", std::string action="[action-not-set]", std::string menu="[branching-menu-identifier-not-set]");
         ~MenuItem();

         void set_keyboard_input(std::string keyboard_input);
         void set_label(std::string label);
         void set_action(std::string action);
         void set_menu(std::string menu);
         std::string get_keyboard_input();
         std::string get_label();
         std::string get_action();
         std::string get_menu();
      };
   }
}



