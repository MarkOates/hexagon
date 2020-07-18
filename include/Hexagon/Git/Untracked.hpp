#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class Untracked
      {
      private:
         std::string current_project_directory;

      public:
         Untracked(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~Untracked();


      std::string get_shell_response();
      std::string build_tracked_files_shell_command();
      };
   }
}



