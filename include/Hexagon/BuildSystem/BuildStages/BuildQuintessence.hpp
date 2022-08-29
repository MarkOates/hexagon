#pragma once


#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace BuildStages
      {
         class BuildQuintessence : public Hexagon::BuildSystem::BuildStages::Base
         {
         private:
            std::string property;

         public:
            BuildQuintessence(std::string property="[unset-property]");
            ~BuildQuintessence();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



