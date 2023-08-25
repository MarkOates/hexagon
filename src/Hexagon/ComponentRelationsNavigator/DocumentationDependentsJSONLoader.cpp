

#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>

#include <allegro_flare/useful_php.h>
#include <filesystem>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace ComponentRelationsNavigator
{


DocumentationDependentsJSONLoader::DocumentationDependentsJSONLoader(std::string dependents_json_filename)
   : dependents_json_filename(dependents_json_filename)
{
}


DocumentationDependentsJSONLoader::~DocumentationDependentsJSONLoader()
{
}


void DocumentationDependentsJSONLoader::set_dependents_json_filename(std::string dependents_json_filename)
{
   this->dependents_json_filename = dependents_json_filename;
}


std::string DocumentationDependentsJSONLoader::get_dependents_json_filename() const
{
   return dependents_json_filename;
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
   if (!(std::filesystem::exists(dependents_json_filename)))
   {
      std::stringstream error_message;
      error_message << "[DocumentationDependentsJSONLoader::dependents_json_file_contents]: error: guard \"std::filesystem::exists(dependents_json_filename)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("DocumentationDependentsJSONLoader::dependents_json_file_contents: error: guard \"std::filesystem::exists(dependents_json_filename)\" not met");
   }
   return php::file_get_contents(dependents_json_filename);
}


} // namespace ComponentRelationsNavigator
} // namespace Hexagon


