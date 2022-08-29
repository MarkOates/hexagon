#pragma once


#include <Hexagon/BuildSystem/BuildStages/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace BuildStages
      {
         class Basic : public Hexagon::BuildSystem::BuildStages::Base
         {
         private:
            std::string property;

         public:
            Basic(std::string property="[unset-property]");
            ~Basic();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



