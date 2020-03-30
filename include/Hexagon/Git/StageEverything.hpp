#pragma once


#include <string>


namespace Hexagon
{
   namespace Git
   {
      class StageEverything
      {
      private:
         std::string current_project_directory;

      public:
         StageEverything(std::string current_project_directory="/Users/markoates/Repos/hexagon/");
         ~StageEverything();


      bool stage_everything();
      };
   }
}



