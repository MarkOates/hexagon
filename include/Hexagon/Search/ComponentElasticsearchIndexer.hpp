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


      std::string generate_uid();
      bool import_or_update();
      };
   }
}



