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

      protected:


      public:
         RemoteSyncChecker(std::string repo_name="blast", std::string repos_directory="~/Repos");
         ~RemoteSyncChecker();

         std::string get_repo_name() const;
         std::string get_repos_directory() const;
         bool is_in_sync_with_remote();
      };
   }
}



