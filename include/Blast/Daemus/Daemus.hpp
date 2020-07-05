#pragma once


#include <string>


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
      void run_build_quintessence_file(std::string project_directory="", std::string quintessence_filename="");
      std::string execute_command(std::string command="");
      void output_pid();
      };
   }
}



