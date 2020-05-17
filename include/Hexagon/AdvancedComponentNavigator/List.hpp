#pragma once


#include <Blast/Project/Component.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace AdvancedComponentNavigator
   {
      class List
      {
      private:
         std::string project_root_directory;

      public:
         List(std::string project_root_directory="");
         ~List();


      std::vector<std::string> component_names();
      std::vector<Blast::Project::Component> components_sorted_by_most_recent();
      std::vector<Blast::Project::Component> components();
      };
   }
}



