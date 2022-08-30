#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/ProjectComponentNavigator/ProjectComponentNavigator.hpp>
#include <functional>
#include <map>
#include <string>


namespace Hexagon
{
   namespace ProjectComponentNavigator
   {
      class EventController
      {
      private:
         Hexagon::ProjectComponentNavigator::ProjectComponentNavigator* component;
         std::map<std::string, std::function<void(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator&)>> event_dictionary;

      public:
         EventController(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator* component=nullptr, std::map<std::string, std::function<void(Hexagon::ProjectComponentNavigator::ProjectComponentNavigator&)>> event_dictionary={});
         ~EventController();

         void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      };
   }
}



