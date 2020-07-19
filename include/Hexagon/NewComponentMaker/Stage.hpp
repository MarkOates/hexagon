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
         bool shell_command_has_executed;
         std::string last_executed_shell_response;
         std::string command;

      public:
         Stage(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~Stage();


         std::string get_current_project_directory();
      std::string get_shell_response();
      std::vector<std::string> get_shell_response_lines();
      std::string build_shell_command();
      };
   }
}



