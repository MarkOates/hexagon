#pragma once


#include <Hexagon/System/System.hpp>
#include <allegro5/allegro.h>
#include <functional>
#include <map>
#include <string>


namespace Hexagon
{
   namespace System
   {
      class EventController
      {
      private:
         Hexagon::System::System* system;
         std::map<std::string, std::function<bool(Hexagon::System::System&)>> function_mapping;

      protected:


      public:
         EventController(Hexagon::System::System* system=nullptr, std::map<std::string, std::function<bool(Hexagon::System::System&)>> function_mapping=Hexagon::System::EventController::get_default_function_mapping());
         ~EventController();

         static std::map<std::string, std::function<bool(Hexagon::System::System&)>> get_default_function_mapping();
         void process_local_event(std::string event_name="[this-event-name-is-a-default-that-represents-undefined]");
         void process_event(ALLEGRO_EVENT* event_ptr=nullptr);
      };
   }
}



