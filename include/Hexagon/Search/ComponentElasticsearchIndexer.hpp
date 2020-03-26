#pragma once


#include <Blast/Project/Component.hpp>


namespace Hexagon
{
   namespace Search
   {
      class ComponentElasticsearchIndexer
      {
      private:
         Blast::Project::Component* component;

      public:
         ComponentElasticsearchIndexer();
         ~ComponentElasticsearchIndexer();


      bool import_or_update(Blast::Project::Component* component=nullptr);
      };
   }
}



