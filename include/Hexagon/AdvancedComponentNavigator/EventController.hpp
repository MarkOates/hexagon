#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedComponentNavigator/AdvancedComponentNavigator.hpp>
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
         Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator* component;
         std::map<std::string, std::function<void(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator&)>> event_dictionary;

      protected:


      public:
         EventController(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator* component=nullptr, std::map<std::string, std::function<void(Hexagon::AdvancedComponentNavigator::AdvancedComponentNavigator&)>> event_dictionary={});
         ~EventController();

         void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      };
   }
}



