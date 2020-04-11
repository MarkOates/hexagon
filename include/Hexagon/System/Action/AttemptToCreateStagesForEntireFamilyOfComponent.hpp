#pragma once


#include <Hexagon/Action.hpp>
#include <Hexagon/StageInterface.hpp>
#include <string>
#include <vector>


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
            std::vector<StageInterface*> stages;

         public:
            AttemptToCreateStagesForEntireFamilyOfComponent(std::string component_name="");
            ~AttemptToCreateStagesForEntireFamilyOfComponent();


            std::string get_component_name();
         void create_code_editor_stages_for_component_names();
         bool execute() override;
         };
      }
   }
}



