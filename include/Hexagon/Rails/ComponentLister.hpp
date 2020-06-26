#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace Rails
   {
      class ComponentLister
      {
      private:
         std::string project_root_directory;

      public:
         ComponentLister(std::string project_root_directory="");
         ~ComponentLister();


      std::vector<std::string> model_filenames();
      };
   }
}



