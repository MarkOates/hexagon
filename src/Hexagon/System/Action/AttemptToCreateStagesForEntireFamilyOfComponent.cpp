

#include <Hexagon/System/Action/AttemptToCreateStagesForEntireFamilyOfComponent.hpp>



namespace Hexagon
{
namespace System
{
namespace Action
{


AttemptToCreateStagesForEntireFamilyOfComponent::AttemptToCreateStagesForEntireFamilyOfComponent(std::string component_name)
   : ::Action("System::Action::AttemptToCreateStagesFromEntireFamilyOfComponent", ActionData())
   , component_name(component_name)
{
}


AttemptToCreateStagesForEntireFamilyOfComponent::~AttemptToCreateStagesForEntireFamilyOfComponent()
{
}


std::string AttemptToCreateStagesForEntireFamilyOfComponent::run()
{
return "Hello World!";
}
} // namespace Action
} // namespace System
} // namespace Hexagon


