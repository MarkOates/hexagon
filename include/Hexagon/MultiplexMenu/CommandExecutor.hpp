#pragma once


#include <Hexagon/MultiplexMenu/MultiplexMenu.hpp>
#include <Hexagon/StageInterface.hpp>
#include <string>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class CommandExecutor
      {
      private:
         StageInterface* stage_to_send_messages_to;
         Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu;
         void send_message_to_stage(std::string message="[message-identifier-set]");

      protected:


      public:
         CommandExecutor(StageInterface* stage_to_send_messages_to=nullptr, Hexagon::MultiplexMenu::MultiplexMenu* multiplex_menu=nullptr);
         ~CommandExecutor();

         bool execute();
      };
   }
}



