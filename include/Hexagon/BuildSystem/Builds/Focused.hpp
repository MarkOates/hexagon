#pragma once


#include <Hexagon/BuildSystem/Builds/Base.hpp>
#include <string>


namespace Hexagon
{
   namespace BuildSystem
   {
      namespace Builds
      {
         class Focused : public Hexagon::BuildSystem::Builds::Base
         {
         private:
            std::string property;

         public:
            Focused(std::string property="[unset-property]");
            ~Focused();

            std::string get_property() const;
            bool property_is(std::string possible_type="");
         };
      }
   }
}



