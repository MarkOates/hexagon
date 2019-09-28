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
         List();
         ~List();


      std::vector<std::string> components();
      };
   }
}



