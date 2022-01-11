#pragma once


#include <Hexagon/Daemus/Daemus.hpp>
#include <string>


namespace Hexagon
{
   namespace Daemus
   {
      class NetworkMessageEventController
      {
      private:
         Hexagon::Daemus::Daemus* daemus;

      public:
         NetworkMessageEventController();
         ~NetworkMessageEventController();

         bool process_message(std::string message="");
      };
   }
}



