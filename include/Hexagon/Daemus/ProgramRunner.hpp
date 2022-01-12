#pragma once


#include <Blast/Project/Component.hpp>
#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace Daemus
   {
      class ProgramRunner
      {
      private:
         std::string quintessence_build_executable;
         std::string daemus_build_file_directory;
         std::string daemus_build_filename;

      public:
         ProgramRunner(std::string quintessence_build_executable="/Users/markoates/Repos/blast/bin/programs/quintessence_from_yaml");
         ~ProgramRunner();

         std::string get_daemus_build_file_directory();
         std::string get_daemus_build_filename();
         void run();
         void process_oldest_file_in_builds_folder();
         void run_full_rebuild();
         void run_in_holding_pattern();
         void run_simple_echo_command();
         void run_simple_sleep_command();
         void run_once(std::string project_directory="");
         void cd_to_project_directory_and_run_with_rerun(std::string project_directory="");
         void watch_for_buildfile(std::string project_directory="");
         void run_with_rerun(std::string project_directory="");
         std::string execute_command(std::string command="");
         std::vector<Hexagon::Testing::GoogleTestRunTestResult> run_component_test(Blast::Project::Component component={});
         void run_build_quintessence_file(std::string project_directory="", std::string quintessence_filename="");
         void output_pid();
         std::string __execute_command(std::string command="", bool output_to_stdout=true);
         static std::string find_oldest_filename(std::string path="/Users/markoates/Repos/hexagon/bin/programs/data/builds/pending");
      };
   }
}



