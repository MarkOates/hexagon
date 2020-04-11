#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/StageInterface.hpp>
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
            StageInterface* stages;

         public:
            AttemptToCreateStagesForEntireFamilyOfComponent(std::string component_name="");
            ~AttemptToCreateStagesForEntireFamilyOfComponent();


         bool execute() override;
         };
      }
   }
}



