

#include <Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent.hpp>
#include <sstream>
#include <Blast/Project/Component.hpp>


namespace Hexagon
{
namespace System
{
namespace Action
{


AttemptToCreateStagesForEntireFamilyOfComponent::AttemptToCreateStagesForEntireFamilyOfComponent(std::string component_name)
   : ::Action("System::Action::AttemptToCreateStagesFromEntireFamilyOfComponent", ActionData())
   , component_name(component_name)
   , stages({})
{
}


AttemptToCreateStagesForEntireFamilyOfComponent::~AttemptToCreateStagesForEntireFamilyOfComponent()
{
}


std::string AttemptToCreateStagesForEntireFamilyOfComponent::get_component_name()
{
   return component_name;
}


bool AttemptToCreateStagesForEntireFamilyOfComponent::execute()
{
Blast::Project::Component component(get_component_name());
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
return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


