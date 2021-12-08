#pragma once


#include <Blast/Project/Component.hpp>
#include <vector>


namespace Hexagon
{
   namespace ComponentRelationsNavigator
   {
      class ComponentRelations
      {
      private:
         Blast::Project::Component component;

      public:
         ComponentRelations();
         ~ComponentRelations();

         std::vector<Blast::Project::Component> build_dependents();
         std::vector<Blast::Project::Component> build_relatives();
         std::vector<Blast::Project::Component> build_dependencies();
      };
   }
}



