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
         std::string dependents_json_filename;
         std::string dependents_json_file_contents();
         bool dependents_json_file_exists();

      protected:


      public:
         DocumentationDependentsJSONLoader();
         ~DocumentationDependentsJSONLoader();

         std::string get_dependents_json_filename() const;
         std::vector<std::string> build_dependent_names_for_component_name(std::string component_name="");
      };
   }
}



