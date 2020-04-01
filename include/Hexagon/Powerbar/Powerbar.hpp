#pragma once




namespace Hexagon
{
   namespace Powerbar
   {
      class Powerbar
      {
      private:
         bool files_are_modified;
         bool files_are_committed;
         bool commits_are_in_sync_with_remote;

      public:
         Powerbar(bool files_are_modified=true, bool files_are_committed=true, bool commits_are_in_sync_with_remote=true);
         ~Powerbar();


         bool get_files_are_modified();
         bool get_files_are_committed();
         bool get_commits_are_in_sync_with_remote();
      };
   }
}



