#pragma once


#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace BuildStages
      {
         class BuildPrograms : public Hexagon::BuildSystem::BuildStages::Base
         {
         private:
            std::string property;

         public:
            BuildPrograms(std::string property="[unset-property]");
            ~BuildPrograms();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



