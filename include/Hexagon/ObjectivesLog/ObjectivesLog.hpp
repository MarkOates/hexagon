#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace ObjectivesLog
   {
      class ObjectivesLog
      {
      private:
         std::vector<std::string> objectives;

      public:
         ObjectivesLog();
         ~ObjectivesLog();

         std::string run();
      };
   }
}



