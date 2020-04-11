

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
   , stages(nullptr)
{
}


AttemptToCreateStagesForEntireFamilyOfComponent::~AttemptToCreateStagesForEntireFamilyOfComponent()
{
}


bool AttemptToCreateStagesForEntireFamilyOfComponent::execute()
{
if (!stages)
{
   std::stringstream error_message;

   error_message << "[Hexagon/System/Action/"
                 << "AttemptToCreateCodeEditorStagesForEntireFamilyOfComponent"
                 << " error:] "
                 << "cannot \"" << __FUNCTION__ << "\" with nullptr stages";
   throw std::runtime_error(error_message.str());
}
return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


