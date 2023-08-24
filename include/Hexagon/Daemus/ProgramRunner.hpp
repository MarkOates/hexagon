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
         enum WatchMode
         {
            UNDEFINED = 0,
            WATCH_FOR_CHANGES_IN_TREE,
            WATCH_FOR_CHANGE_IN_BUILDFILE,
         };
         std::string quintessence_build_executable;
         std::string daemus_buildfile_directory;
         std::string daemus_buildfile_filename;
         Hexagon::Daemus::ProgramRunner::WatchMode watch_mode;
         std::string execute_command(std::string command="");
         std::string __execute_command(std::string command="", bool output_to_stdout=true);

      protected:


      public:
         ProgramRunner(std::string quintessence_build_executable="/Users/markoates/Repos/blast/bin/programs/quintessence_from_yaml");
         ~ProgramRunner();

         std::string get_daemus_buildfile_directory() const;
         std::string get_daemus_buildfile_filename() const;
         Hexagon::Daemus::ProgramRunner::WatchMode get_watch_mode() const;
         void run(bool watch_for_changes_in_tree_and_not_buildfile=true);
         void process_oldest_file_in_builds_folder();
         void run_full_rebuild();
         void run_in_holding_pattern();
         void run_simple_echo_command();
         void run_simple_sleep_command();
         void run_once(std::string project_directory="");
         void cd_to_project_directory_and_run_with_rerun(std::string project_directory="");
         void watch_for_buildfile(std::string project_directory="");
         void run_with_rerun(std::string project_directory="");
         std::vector<Hexagon::Testing::GoogleTestRunTestResult> run_component_test(Blast::Project::Component component={});
         void run_build_quintessence_file(std::string project_directory="", std::string quintessence_filename="");
         void output_pid();
         static std::string find_oldest_filename(std::string path="/Users/markoates/Repos/hexagon/bin/programs/data/builds/pending", bool ignore_dotfiles=true);
      };
   }
}



