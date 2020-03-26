#pragma once


#include <Blast/Project/Component.hpp>
#include <string>


namespace Hexagon
{
   namespace Search
   {
      class ComponentElasticsearchIndexer
      {
      private:
         Blast::Project::Component* component;

      public:
         ComponentElasticsearchIndexer(Blast::Project::Component* component=nullptr);
         ~ComponentElasticsearchIndexer();


      void guard_nullptr_component(std::string function_name="unset_function_name");
      std::string generate_uid();
      std::string generate_index_shell_command();
      std::string import_or_update();
      };
   }
}



