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
         std::string index_name;

      protected:


      public:
         ComponentElasticsearchIndexer(Blast::Project::Component* component=nullptr, std::string index_name="components_dummy");
         ~ComponentElasticsearchIndexer();

         std::string get_index_name() const;
         std::string generate_uid();
         std::string generate_index_shell_command();
         std::string import_or_update();
      };
   }
}



