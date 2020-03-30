#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class Staged
      {
      private:
         std::string current_project_directory;

      public:
         Staged(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~Staged();


      std::string get_commit_everything_shell_command();
      std::string get_staged_response();
      };
   }
}



