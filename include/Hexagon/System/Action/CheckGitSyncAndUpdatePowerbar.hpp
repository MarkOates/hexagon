#pragma once


#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class CheckGitSyncAndUpdatePowerbar
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



