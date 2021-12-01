#pragma once


#include <string>


namespace Blast
{
   namespace Daemus
   {
      class ProgramRunner
      {
      private:
         std::string daemus_build_file_directory;
         std::string daemus_build_filename;

      public:
         ProgramRunner();
         ~ProgramRunner();

         std::string get_daemus_build_file_directory();
         std::string get_daemus_build_filename();
         void run();
         void run_in_holding_pattern();
         void run_once(std::string project_directory="");
         void cd_to_project_directory_and_run_with_rerun(std::string project_directory="");
         void watch_for_buildfile(std::string project_directory="");
         void run_with_rerun(std::string project_directory="");
         std::string execute_command(std::string command="");
      };
   }
}



