#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace NewComponentMaker
   {
      class NewComponentMaker
      {
      private:
         std::string current_project_directory;
         std::string component_name;
         bool shell_command_has_executed;
         std::string last_executed_shell_response;
         std::string path_to_executable;

      public:
         NewComponentMaker(std::string current_project_directory="/Users/markoates/Repos/hexagon/", std::string component_name="");
         ~NewComponentMaker();

         std::string get_current_project_directory();
         std::string get_shell_response();
         std::vector<std::string> get_shell_response_lines();
         std::string build_shell_command();
      };
   }
}



