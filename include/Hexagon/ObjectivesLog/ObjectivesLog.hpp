#pragma once


#include <Hexagon/ObjectivesLog/Objective.hpp>
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

         std::vector<Hexagon::ObjectivesLog::Objective> &get_objectives_ref();
      };
   }
}



