#pragma once


#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class CheckGitUntrackedModifiedStagedAndUpdatePowerbar
         {
         private:

         public:
            CheckGitUntrackedModifiedStagedAndUpdatePowerbar();
            ~CheckGitUntrackedModifiedStagedAndUpdatePowerbar();


         std::string run();
         };
      }
   }
}



