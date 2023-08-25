#pragma once


#include <Blast/Project/Component.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace ComponentRelationsNavigator
   {
      class ComponentRelations
      {
      private:
         Blast::Project::Component component;
         bool simplify_relatives_list;
         static std::string build_implicit_json_dependents_filename_for_project(std::string project_root="[unset-project_root]");
         static bool valid_project_root(std::string* project_root=nullptr);

      protected:


      public:
         ComponentRelations(Blast::Project::Component component={});
         ~ComponentRelations();

         std::vector<std::string> build_dependents_list();
         std::vector<std::string> build_relatives_list();
         std::vector<std::string> build_dependencies_list();
      };
   }
}



