#pragma once


#include <Blast/Daemus/Daemus.hpp>
#include <string>


namespace Blast
{
   namespace Daemus
   {
      class NetworkMessageEventController
      {
      private:
         Blast::Daemus::Daemus* daemus;

      public:
         NetworkMessageEventController();
         ~NetworkMessageEventController();

         bool process_message(std::string message="");
      };
   }
}



