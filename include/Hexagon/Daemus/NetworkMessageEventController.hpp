#pragma once


#include <Hexagon/Daemus/ProgramRunner.hpp>
#include <string>


namespace Hexagon
{
   namespace Daemus
   {
      class NetworkMessageEventController
      {
      private:
         Hexagon::Daemus::ProgramRunner* program_runner;

      public:
         NetworkMessageEventController();
         ~NetworkMessageEventController();

         bool process_message(std::string message="");
      };
   }
}



