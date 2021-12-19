

#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>
#include <lib/nlohmann/json.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <allegro_flare/useful_php.h>
#include <stdexcept>
#include <sstream>
#include <Blast/FileExistenceChecker.hpp>


namespace Hexagon
{
namespace ComponentRelationsNavigator
{


DocumentationDependentsJSONLoader::DocumentationDependentsJSONLoader()
   : DEPENDENTS_JSON_FILENAME("/Users/markoates/Repos/Krampus21/documentation/dependents.json")
{
}


DocumentationDependentsJSONLoader::~DocumentationDependentsJSONLoader()
{
}


std::string DocumentationDependentsJSONLoader::get_DEPENDENTS_JSON_FILENAME()
{
   return DEPENDENTS_JSON_FILENAME;
}


std::vector<std::string> DocumentationDependentsJSONLoader::build_dependent_names_for_component_name(std::string component_name)
{
   nlohmann::json json = nlohmann::json::parse(dependents_json_file_contents());
   nlohmann::json json_elements_for_component_name = json[component_name];

   std::vector<std::string> result;
   for (nlohmann::json::iterator it = json_elements_for_component_name.begin();
        it != json_elements_for_component_name.end();
        ++it)
   {
       result.push_back(*it);
   }

   return result;
}

std::string DocumentationDependentsJSONLoader::dependents_json_file_contents()
{
   if (!(dependents_json_file_exists()))
      {
         std::stringstream error_message;
         error_message << "DocumentationDependentsJSONLoader" << "::" << "dependents_json_file_contents" << ": error: " << "guard \"dependents_json_file_exists()\" not met";
         throw std::runtime_error(error_message.str());
      }
   return php::file_get_contents(get_DEPENDENTS_JSON_FILENAME());
}

bool DocumentationDependentsJSONLoader::dependents_json_file_exists()
{
   return Blast::FileExistenceChecker(get_DEPENDENTS_JSON_FILENAME()).exists();
}
} // namespace ComponentRelationsNavigator
} // namespace Hexagon

