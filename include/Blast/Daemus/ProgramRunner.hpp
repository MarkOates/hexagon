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


      std::string __replace(std::string str="", std::string from="", std::string to="");
      std::string execute_command(std::string command="");
      void block_execution_with_rerun_pause();
      void run_full_rebuild();
      void run();
      void run_with_block_after_command();
      };
   }
}



