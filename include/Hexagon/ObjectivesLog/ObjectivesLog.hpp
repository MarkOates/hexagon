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

      protected:


      public:
         ObjectivesLog(std::vector<Hexagon::ObjectivesLog::Objective> objectives={});
         ~ObjectivesLog();

         std::vector<Hexagon::ObjectivesLog::Objective> &get_objectives_ref();
         void add_objective(Hexagon::ObjectivesLog::Objective objective={});
      };
   }
}



