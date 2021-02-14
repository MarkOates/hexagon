#pragma once


#include <string>


namespace Hexagon
{
   namespace Search
   {
      class ComponentElasticsearchIndex
      {
      private:

      public:
         ComponentElasticsearchIndex();
         ~ComponentElasticsearchIndex();

         std::string get_index_name();
         std::string get_index_mapping();
      };
   }
}



