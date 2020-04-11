

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
return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


