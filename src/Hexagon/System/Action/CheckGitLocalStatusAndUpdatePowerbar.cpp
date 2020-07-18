

#include <Hexagon/System/Action/CheckGitLocalStatusAndUpdatePowerbar.hpp>
#include <stdexcept>
#include <sstream>


namespace Hexagon
{
namespace System
{
namespace Action
{


CheckGitLocalStatusAndUpdatePowerbar::CheckGitLocalStatusAndUpdatePowerbar(Hexagon::Powerbar::Powerbar* powerbar)
   : ::Action("Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar", ActionData())
   , powerbar(powerbar)
{
}


CheckGitLocalStatusAndUpdatePowerbar::~CheckGitLocalStatusAndUpdatePowerbar()
{
}


bool CheckGitLocalStatusAndUpdatePowerbar::execute()
{
if (!(powerbar))
   {
      std::stringstream error_message;
      error_message << "CheckGitLocalStatusAndUpdatePowerbar" << "::" << "execute" << ": error: " << "guard \"powerbar\" not met";
      throw std::runtime_error(error_message.str());
   }
return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


