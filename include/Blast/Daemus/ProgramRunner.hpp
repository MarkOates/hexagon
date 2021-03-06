#pragma once


#include <string>


namespace Blast
{
   namespace Daemus
   {
      class ProgramRunner
      {
      private:

      public:
         ProgramRunner();
         ~ProgramRunner();

         void run();
         void run_in_holding_pattern();
         void run_once(std::string project_directory="");
         void cd_to_project_directory_and_run_with_rerun(std::string project_directory="");
         void run_with_rerun(std::string project_directory="");
         std::string execute_command(std::string command="");
      };
   }
}



