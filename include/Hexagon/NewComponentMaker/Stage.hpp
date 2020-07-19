#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace NewComponentMaker
   {
      class Stage
      {
      private:
         std::string current_project_directory;

      public:
         Stage(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~Stage();


         std::string get_current_project_directory();
      std::string get_shell_response();
      std::vector<std::string> get_shell_response_lines();
      std::string build_tracked_files_shell_command();
      };
   }
}



