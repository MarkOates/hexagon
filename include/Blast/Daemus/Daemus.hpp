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
      std::string execute_command(std::string command="");
      void output_pid();
      };
   }
}



