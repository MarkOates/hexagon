#pragma once


#include <string>


namespace Hexagon
{
   namespace ComponentRelationsNavigator
   {
      class DocumentationDependentsJSONLoader
      {
      private:

      public:
         DocumentationDependentsJSONLoader();
         ~DocumentationDependentsJSONLoader();

         std::string run();
      };
   }
}



