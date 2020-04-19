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

      public:
         Pusher(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~Pusher();


      std::string get_push_shell_command();
      std::string push();
      };
   }
}



