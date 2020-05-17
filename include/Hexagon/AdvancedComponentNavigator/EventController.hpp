#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <functional>
#include <map>
#include <string>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class EventController
      {
      private:
         Hexagon::AdvancedComponentNavigator::Stage* stage;
         std::map<std::string, std::function<void(Stage&)>> event_dictionary;

      public:
         EventController(Hexagon::AdvancedComponentNavigator::Stage* stage=nullptr, std::map<std::string, std::function<void(Stage&)>> event_dictionary={});
         ~EventController();


      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      };
   }
}



