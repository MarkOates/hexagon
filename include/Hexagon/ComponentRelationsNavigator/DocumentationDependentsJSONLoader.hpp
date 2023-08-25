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

      protected:


      public:
         DocumentationDependentsJSONLoader(std::string dependents_json_filename="/Users/markoates/Repos/hexagon/documentation/dependents.json");
         ~DocumentationDependentsJSONLoader();

         void set_dependents_json_filename(std::string dependents_json_filename);
         std::string get_dependents_json_filename() const;
         std::vector<std::string> build_dependent_names_for_component_name(std::string component_name="");
      };
   }
}



