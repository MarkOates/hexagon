

#include <Hexagon/Powerbar/Powerbar.hpp>



namespace Hexagon
{
namespace Powerbar
{


Powerbar::Powerbar(bool files_are_modified, bool files_are_committed, bool commits_are_in_sync_with_remote)
   : files_are_modified(files_are_modified)
   , files_are_committed(files_are_committed)
   , commits_are_in_sync_with_remote(commits_are_in_sync_with_remote)
   , focus_timer_started_at(0)
{
}


Powerbar::~Powerbar()
{
}


void Powerbar::set_files_are_modified(bool files_are_modified)
{
   this->files_are_modified = files_are_modified;
}


void Powerbar::set_files_are_committed(bool files_are_committed)
{
   this->files_are_committed = files_are_committed;
}


void Powerbar::set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote)
{
   this->commits_are_in_sync_with_remote = commits_are_in_sync_with_remote;
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


std::time_t Powerbar::get_focus_timer_started_at()
{
   return focus_timer_started_at;
}


} // namespace Powerbar
} // namespace Hexagon


