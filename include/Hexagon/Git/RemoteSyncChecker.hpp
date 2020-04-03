#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class RemoteSyncChecker
      {
      private:

      public:
         RemoteSyncChecker();
         ~RemoteSyncChecker();


      std::string run();
      };
   }
}



