

#include <Hexagon/Powerbar/Powerbar.hpp>



namespace Hexagon
{
namespace Powerbar
{


Powerbar::Powerbar(bool files_are_modified, bool files_are_committed, bool commits_are_in_sync_with_remote)
   : files_are_modified(files_are_modified)
   , files_are_committed(files_are_committed)
   , commits_are_in_sync_with_remote(commits_are_in_sync_with_remote)
{
}


Powerbar::~Powerbar()
{
}


bool Powerbar::get_files_are_modified()
{
   return files_are_modified;
}


bool Powerbar::get_files_are_committed()
{
   return files_are_committed;
}


bool Powerbar::get_commits_are_in_sync_with_remote()
{
   return commits_are_in_sync_with_remote;
}


} // namespace Powerbar
} // namespace Hexagon


