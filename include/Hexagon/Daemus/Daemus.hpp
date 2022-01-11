#pragma once


#include <Blast/Project/Component.hpp>
#include <Hexagon/Daemus/Builds/Base.hpp>
#include <Hexagon/Daemus/Builds/ExtrapolateQuintessence.hpp>
#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace Daemus
   {
      class Daemus
      {
      private:
         std::string quintessence_build_executable;
         Hexagon::Daemus::Builds::Base* current_build;
         std::vector<Hexagon::Daemus::Builds::Base*> builds;

      public:
         Daemus(std::string quintessence_build_executable="/Users/markoates/Repos/blast/bin/programs/quintessence_from_yaml");
         ~Daemus();

         Hexagon::Daemus::Builds::Base* get_current_build();
         std::vector<Hexagon::Daemus::Builds::Base*> &get_builds_ref();
         Hexagon::Daemus::Builds::ExtrapolateQuintessence* create_extrapolate_quintessence_build();
         void run_full_rebuild();
         void run_simple_echo_command();
         void run_simple_sleep_command();
         std::vector<Hexagon::Testing::GoogleTestRunTestResult> run_component_test(Blast::Project::Component component={});
         void run_build_quintessence_file(std::string project_directory="", std::string quintessence_filename="");
         void output_pid();
         std::string execute_command(std::string command="", bool output_to_stdout=true);
      };
   }
}



