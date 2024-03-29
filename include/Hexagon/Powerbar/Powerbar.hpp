#pragma once


#include <ctime>


namespace Hexagon
{
   namespace Powerbar
   {
      class Powerbar
      {
      private:
         bool files_are_modified;
         bool files_are_staged;
         bool files_are_untracked;
         bool files_are_committed;
         bool commits_are_in_sync_with_remote;
         std::time_t focus_timer_started_at;
         float focus_timer_duration_sec;

      protected:


      public:
         Powerbar(bool files_are_modified=false, bool files_are_staged=false, bool files_are_untracked=false, bool files_are_committed=true, bool commits_are_in_sync_with_remote=true);
         ~Powerbar();

         void set_files_are_modified(bool files_are_modified);
         void set_files_are_staged(bool files_are_staged);
         void set_files_are_untracked(bool files_are_untracked);
         void set_files_are_committed(bool files_are_committed);
         void set_commits_are_in_sync_with_remote(bool commits_are_in_sync_with_remote);
         bool get_files_are_modified() const;
         bool get_files_are_staged() const;
         bool get_files_are_untracked() const;
         bool get_files_are_committed() const;
         bool get_commits_are_in_sync_with_remote() const;
         std::time_t get_focus_timer_started_at() const;
         float get_focus_timer_duration_sec() const;
      };
   }
}



