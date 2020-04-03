#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class RemoteSyncChecker
      {
      private:
         std::string repo_name;
         std::string repos_directory;

      public:
         RemoteSyncChecker(std::string repo_name="blast", std::string repos_directory="~/Repos");
         ~RemoteSyncChecker();


         std::string get_repo_name();
         std::string get_repos_directory();
      bool is_in_sync_with_remote();
      };
   }
}



