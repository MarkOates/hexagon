#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class CommitStagedWithMessage
      {
      private:
         std::string current_project_directory;
         std::string message;

      public:
         CommitStagedWithMessage(std::string current_project_directory="/Users/markoates/Repos/hexagon/", std::string message="auto commit");
         ~CommitStagedWithMessage();


      std::string build_sanitized_commit_message();
      std::string build_shell_command();
      bool commit();
      };
   }
}



