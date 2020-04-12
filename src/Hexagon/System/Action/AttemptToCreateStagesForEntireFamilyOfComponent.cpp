

#include <Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent.hpp>
#include <Hexagon/CodeEditor/Stage.hpp>
#include <Blast/Project/ComponentRelativeLister.hpp>
#include <sstream>
#include <Blast/Project/Component.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


AttemptToCreateStagesForEntireFamilyOfComponent::AttemptToCreateStagesForEntireFamilyOfComponent(std::string component_name, std::vector<StageInterface*>* stages)
   : ::Action("System::Action::AttemptToCreateStagesFromEntireFamilyOfComponent", ActionData())
   , component_name(component_name)
   , stages(stages)
{
}


AttemptToCreateStagesForEntireFamilyOfComponent::~AttemptToCreateStagesForEntireFamilyOfComponent()
{
}


std::string AttemptToCreateStagesForEntireFamilyOfComponent::get_component_name()
{
   return component_name;
}


void AttemptToCreateStagesForEntireFamilyOfComponent::create_code_editor_stages_for_component_names()
{
return;

}

bool AttemptToCreateStagesForEntireFamilyOfComponent::execute()
{
Blast::Project::Component component(get_component_name());
if (!stages)
{
   throw std::runtime_error("stages must be present");
}
if (!component.exists())
{
   std::stringstream error_message;
   error_message << "["
                 << "Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent"
                 << " error:]"
                 << " can not execute with a component that does not exist.";
   throw std::runtime_error(error_message.str());
   return false;
}

Blast::Project::ComponentRelativeLister relative_lister(&component);
std::vector<std::string> family_member_component_names = relative_lister.list_component_relative_names();

// create_st

for (auto &family_member_component_name : family_member_component_names)
{
   // create the stage
   //CodeEditor::Stage *code_editor_stage = new CodeEditor::Stage;

   // push it back into the stages
}

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


