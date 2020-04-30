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


      std::string execute_command(std::string command="");
      void output_pid();
      void run_full_rebuild();
      };
   }
}



