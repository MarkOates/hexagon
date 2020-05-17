#pragma once


#include <Hexagon/ActionData.hpp>
#include <Hexagon/AdvancedComponentNavigator/Stage.hpp>
#include <string>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class EventController
      {
      private:
         Hexagon::AdvancedComponentNavigator::Stage* stage;

      public:
         EventController(Hexagon::AdvancedComponentNavigator::Stage* stage=nullptr);
         ~EventController();


      void process_local_event(std::string event_name="", ActionData action_data=ActionData());
      };
   }
}



