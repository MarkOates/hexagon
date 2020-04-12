#pragma once


#include <Hexagon/Action.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class CheckGitSyncAndUpdatePowerbar : public ::Action
         {
         private:

         public:
            CheckGitSyncAndUpdatePowerbar();
            ~CheckGitSyncAndUpdatePowerbar();


         std::string run();
         };
      }
   }
}



