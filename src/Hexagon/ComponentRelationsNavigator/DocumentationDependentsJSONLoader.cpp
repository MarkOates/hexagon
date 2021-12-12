

#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>
#include <lib/nlohmann/json.hpp>


namespace Hexagon
{
namespace ComponentRelationsNavigator
{


DocumentationDependentsJSONLoader::DocumentationDependentsJSONLoader()
   : DEPENDENTS_JSON_FILENAME("/Users/markoates/Repos/hexagon/documentation/dependents.json")
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
   nlohmann::json j;
   return {};
}
} // namespace ComponentRelationsNavigator
} // namespace Hexagon


