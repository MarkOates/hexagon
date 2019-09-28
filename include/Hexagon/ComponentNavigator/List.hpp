#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace ComponentNavigator
   {
      class List
      {
      private:
         std::string project_root_directory;

      public:
         List(std::string project_root_directory="");
         ~List();


      std::vector<std::string> components();
      };
   }
}



