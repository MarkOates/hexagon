#pragma once


#include <Hexagon/Action.hpp>
#include <string>


namespace Hexagon
{
   namespace System
   {
      namespace Action
      {
         class AttemptToCreateStagesForEntireFamilyOfComponent : public ::Action
         {
         private:
            std::string component_name;

         public:
            AttemptToCreateStagesForEntireFamilyOfComponent(std::string component_name="");
            ~AttemptToCreateStagesForEntireFamilyOfComponent();


         bool execute() override;
         };
      }
   }
}



