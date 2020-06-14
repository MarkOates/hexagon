#pragma once


#include <Hexagon/System/System.hpp>


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


      void process_event();
      };
   }
}



