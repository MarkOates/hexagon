#pragma once


#include <Blast/Project/Component.hpp>
#include <string>
#include <vector>


namespace Blast
{
   namespace Project
   {
      class ComponentRelativeLister
      {
      private:
         Blast::Project::Component* component;

      public:
         ComponentRelativeLister(Blast::Project::Component* component=nullptr);
         ~ComponentRelativeLister();

         std::vector<std::string> list_component_relative_names();
      };
   }
}



