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


      std::string execute_command(std::string command="");
      void run();
      void run_with_rerun(std::string project_directory="");
      };
   }
}



