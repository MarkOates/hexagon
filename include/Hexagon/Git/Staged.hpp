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


      std::string get_staged_response();
      std::string build_staged_files_shell_command();
      };
   }
}



