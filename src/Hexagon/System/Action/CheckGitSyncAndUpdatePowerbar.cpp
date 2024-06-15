

#include <Hexagon/System/Action/CheckGitSyncAndUpdatePowerbar.hpp>

#include <Hexagon/Git/RemoteSyncChecker.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace System
{
namespace Action
{


CheckGitSyncAndUpdatePowerbar::CheckGitSyncAndUpdatePowerbar(std::string repo_name, std::string repos_directory, Hexagon::Powerbar::Powerbar* powerbar)
   : ::Action("Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar", ActionData())
   , repo_name(repo_name)
   , repos_directory(repos_directory)
   , powerbar(powerbar)
{
}


CheckGitSyncAndUpdatePowerbar::~CheckGitSyncAndUpdatePowerbar()
{
}


std::string CheckGitSyncAndUpdatePowerbar::get_repo_name() const
{
   return repo_name;
}


std::string CheckGitSyncAndUpdatePowerbar::get_repos_directory() const
{
   return repos_directory;
}


bool CheckGitSyncAndUpdatePowerbar::execute()
{
   if (!(powerbar))
   {
      std::stringstream error_message;
      error_message << "[Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar::execute]: error: guard \"powerbar\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Hexagon::System::Action::CheckGitSyncAndUpdatePowerbar::execute]: error: guard \"powerbar\" not met");
   }
   Hexagon::Git::RemoteSyncChecker sync_checker(repo_name, repos_directory);
   bool is_in_sync_with_remote = sync_checker.is_in_sync_with_remote();

   powerbar->set_commits_are_in_sync_with_remote(is_in_sync_with_remote);

   return true;
}


} // namespace Action
} // namespace System
} // namespace Hexagon


