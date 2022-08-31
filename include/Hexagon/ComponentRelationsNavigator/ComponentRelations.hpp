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



