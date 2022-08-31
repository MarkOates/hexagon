#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class Pusher
      {
      private:
         std::string current_project_directory;
         std::string get_push_shell_command();

      protected:


      public:
         Pusher(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~Pusher();

         void validate_result_or_throw_error_on_failure(std::string response="");
         std::string push();
      };
   }
}



