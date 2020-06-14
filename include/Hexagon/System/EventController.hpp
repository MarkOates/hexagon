#pragma once




namespace Hexagon
{
   namespace System
   {
      class EventController
      {
      private:
         System* system;

      public:
         EventController();
         ~EventController();


      void process_event();
      };
   }
}



