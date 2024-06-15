

#include <Hexagon/System/Action/CheckGitLocalStatusAndUpdatePowerbar.hpp>

#include <Hexagon/Git/Modified.hpp>
#include <Hexagon/Git/Staged.hpp>
#include <Hexagon/Git/Untracked.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


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


std::string CheckGitLocalStatusAndUpdatePowerbar::get_current_project_directory() const
{
   return current_project_directory;
}


bool CheckGitLocalStatusAndUpdatePowerbar::execute()
{
   if (!(powerbar))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar::execute]: error: guard \"powerbar\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Action::CheckGitLocalStatusAndUpdatePowerbar::execute]: error: guard \"powerbar\" not met");
   }
   Hexagon::Git::Modified modified(current_project_directory);
   std::vector<std::string> modified_files = modified.get_shell_response();

   Hexagon::Git::Untracked untracked(current_project_directory);
   std::vector<std::string> untracked_files = untracked.get_shell_response();

   Hexagon::Git::Staged staged(current_project_directory);
   std::vector<std::string> staged_files = staged.get_shell_response();

   bool files_are_modified = !modified_files.empty();
   powerbar->set_files_are_modified(files_are_modified);

   bool files_are_untracked = !untracked_files.empty();
   powerbar->set_files_are_untracked(files_are_untracked);

   bool files_are_staged = !staged_files.empty();
   powerbar->set_files_are_staged(files_are_staged);

   return true;
}


} // namespace Action
} // namespace System
} // namespace Hexagon


