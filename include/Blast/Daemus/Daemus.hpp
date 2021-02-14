#pragma once


#include <Blast/Project/Component.hpp>
#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>
#include <string>
#include <vector>


namespace Blast
{
   namespace Daemus
   {
      class Daemus
      {
      private:
         std::string quintessence_build_executable;

      public:
         Daemus(std::string quintessence_build_executable="/Users/markoates/Repos/blast/bin/programs/quintessence_from_yaml");
         ~Daemus();

         void run_full_rebuild();
         void run_simple_echo_command();
         void run_simple_sleep_command();
         std::vector<Hexagon::Testing::GoogleTestRunTestResult> run_component_test(Blast::Project::Component component={});
         void run_build_quintessence_file(std::string project_directory="", std::string quintessence_filename="");
         std::string execute_command(std::string command="", bool output_to_stdout=true);
         void output_pid();
      };
   }
}



