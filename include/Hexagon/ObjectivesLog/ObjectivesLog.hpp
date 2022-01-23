#pragma once


#include <Hexagon/ObjectivesLog/Objective.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace ObjectivesLog
   {
      class ObjectivesLog
      {
      private:
         std::vector<Hexagon::ObjectivesLog::Objective> objectives;

      public:
         ObjectivesLog();
         ~ObjectivesLog();

         std::string run();
      };
   }
}



