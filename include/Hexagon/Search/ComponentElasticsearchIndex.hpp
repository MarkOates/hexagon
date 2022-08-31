#pragma once


#include <string>


namespace Hexagon
{
   namespace Search
   {
      class ComponentElasticsearchIndex
      {
      private:

      protected:


      public:
         ComponentElasticsearchIndex();
         ~ComponentElasticsearchIndex();

         std::string get_index_name();
         std::string get_index_mapping();
      };
   }
}



