

#include <Hexagon/System/Action/CheckGitLocalStatusAndUpdatePowerbar.hpp>
#include <Hexagon/Git/Modified.hpp>
#include <Hexagon/Git/Untracked.hpp>
#include <Hexagon/Git/Staged.hpp>
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
Hexagon::Git::Modified modified;
std::string modified_files = modified.get_shell_response();

Hexagon::Git::Untracked untracked;
std::string untracked_files = untracked.get_shell_response();

Hexagon::Git::Staged staged;
std::string staged_files = staged.get_shell_response();

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


