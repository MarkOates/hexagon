#pragma once


#include <string>
#include <vector>


namespace Hexagon
{
   namespace ComponentRelationsNavigator
   {
      class DocumentationDependentsJSONLoader
      {
      private:
         std::string DEPENDENTS_JSON_FILENAME;

      public:
         DocumentationDependentsJSONLoader();
         ~DocumentationDependentsJSONLoader();

         std::string get_DEPENDENTS_JSON_FILENAME();
         std::vector<std::string> build_dependent_names_for_component_name(std::string component_name="");
         std::string dependents_json_file_contents();
         bool dependents_json_file_exists();
      };
   }
}



