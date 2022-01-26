#pragma once


#include <Hexagon/StageInterface.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace Hexagon
{
   namespace MultiplexMenu
   {
      class MultiplexMenu
      {
      private:
         StageInterface* stage;
         std::vector<std::tuple<std::string, std::string, std::string, std::string>> items;

      public:
         MultiplexMenu(StageInterface* stage=nullptr, std::vector<std::tuple<std::string, std::string, std::string, std::string>> items={});
         ~MultiplexMenu();

         void send_message_to_stage(std::string message="[message-identifier-set]");
      };
   }
}



