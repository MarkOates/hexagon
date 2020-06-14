#pragma once


#include <Hexagon/System/System.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      class EventController
      {
      private:
         ::System* system;

      public:
         EventController(::System* system=nullptr);
         ~EventController();


      void process_local_event(std::string event_name="[event-is-a-default-that-represents-undefined]");
      };
   }
}



