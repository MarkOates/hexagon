#pragma once


#include <Blast/Project/Component.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class ComponentSearcher
      {
      private:
         std::string project_root_directory;
         std::string search_text;

      public:
         ComponentSearcher(std::string project_root_directory="", std::string search_text="");
         ~ComponentSearcher();


      std::vector<Blast::Project::Component> convert_to_components(std::vector<std::string> names={});
      std::vector<std::string> component_names();
      std::vector<Blast::Project::Component> components_sorted_by_most_recent();
      std::vector<Blast::Project::Component> components();
      };
   }
}



