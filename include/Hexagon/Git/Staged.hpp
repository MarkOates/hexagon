#pragma once


#include <string>
#include <vector>


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


         std::string get_current_project_directory();
      std::vector<std::string> get_shell_response();
      std::string build_staged_files_shell_command();
      };
   }
}



