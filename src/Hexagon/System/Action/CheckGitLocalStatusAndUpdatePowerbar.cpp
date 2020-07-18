

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


CheckGitLocalStatusAndUpdatePowerbar::CheckGitLocalStatusAndUpdatePowerbar(std::string current_project_directory, Hexagon::Powerbar::Powerbar* powerbar)
   : ::Action("Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar", ActionData())
   , current_project_directory(current_project_directory)
   , powerbar(powerbar)
{
}


CheckGitLocalStatusAndUpdatePowerbar::~CheckGitLocalStatusAndUpdatePowerbar()
{
}


std::string CheckGitLocalStatusAndUpdatePowerbar::get_current_project_directory()
{
   return current_project_directory;
}


bool CheckGitLocalStatusAndUpdatePowerbar::execute()
{
if (!(powerbar))
   {
      std::stringstream error_message;
      error_message << "CheckGitLocalStatusAndUpdatePowerbar" << "::" << "execute" << ": error: " << "guard \"powerbar\" not met";
      throw std::runtime_error(error_message.str());
   }
Hexagon::Git::Modified modified(current_project_directory);
std::vector<std::string> modified_files = modified.get_shell_response();

Hexagon::Git::Untracked untracked(current_project_directory);
std::vector<std::string> untracked_files = untracked.get_shell_response();

Hexagon::Git::Staged staged(current_project_directory);
std::vector<std::string> staged_files = staged.get_shell_response();

return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


