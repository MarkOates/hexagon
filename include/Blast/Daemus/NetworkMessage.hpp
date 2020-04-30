#pragma once


#include <Blast/Daemus/Daemus.hpp>
#include <string>


namespace Blast
{
   namespace Daemus
   {
      class NetworkMessage
      {
      private:
         Blast::Daemus::Daemus* daemus;

      public:
         NetworkMessage();
         ~NetworkMessage();


      bool process_message(std::string message="");
      };
   }
}



