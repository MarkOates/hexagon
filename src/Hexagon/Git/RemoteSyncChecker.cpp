

#include <Hexagon/Git/RemoteSyncChecker.hpp>
#include <NcursesArt/GithubRepoStatusFetcher.hpp>


namespace Hexagon
{
namespace Git
{


RemoteSyncChecker::RemoteSyncChecker(std::string repo_name, std::string repos_directory)
   : repo_name(repo_name)
   , repos_directory(repos_directory)
{
}


RemoteSyncChecker::~RemoteSyncChecker()
{
}


std::string RemoteSyncChecker::get_repo_name()
{
   return repo_name;
}


std::string RemoteSyncChecker::get_repos_directory()
{
   return repos_directory;
}


bool RemoteSyncChecker::is_in_sync_with_remote()
{
NcursesArt::GithubRepoStatusFetcher fetcher;
return false;

}
} // namespace Git
} // namespace Hexagon


