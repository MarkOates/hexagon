#pragma once


#include <string>


namespace Blast
{
   namespace Daemus
   {
      class Daemus
      {
      private:

      public:
         Daemus();
         ~Daemus();


      void run_full_rebuild();
      void run_simple_echo_command();
      void run_simple_sleep_command();
      std::string execute_command(std::string command="");
      void output_pid();
      };
   }
}



