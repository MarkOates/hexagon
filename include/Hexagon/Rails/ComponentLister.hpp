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
      std::vector<std::string> get_recursive_list_of_files_in_folder(std::string fragment_folder_name="app/models", std::string fragment_extension=".rb");
      };
   }
}



