#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class Modified
      {
      private:
         std::string current_project_directory;

      public:
         Modified(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~Modified();


         std::string get_current_project_directory();
      std::string get_shell_response();
      std::string build_tracked_files_shell_command();
      };
   }
}



