

#include <Hexagon/System/Action/CheckGitSyncAndUpdatePowerbar.hpp>



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


std::string CheckGitSyncAndUpdatePowerbar::get_repo_name()
{
   return repo_name;
}


std::string CheckGitSyncAndUpdatePowerbar::get_repos_directory()
{
   return repos_directory;
}


bool CheckGitSyncAndUpdatePowerbar::execute()
{
//Hexagon::Git::RemoteSyncChecker sync_checker(repo_name, repos_directory);
if (!powerbar)
{
   throw std::runtime_error("asdfa joida f");
}
return true;

}
} // namespace Action
} // namespace System
} // namespace Hexagon


