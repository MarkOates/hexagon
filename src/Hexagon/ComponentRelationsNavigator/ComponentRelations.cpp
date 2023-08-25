

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>

#include <Blast/Project/ComponentDependencyLister.hpp>
#include <Blast/Project/ComponentRelativeLister.hpp>
#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{
namespace ComponentRelationsNavigator
{


ComponentRelations::ComponentRelations(Blast::Project::Component component)
   : component(component)
   , simplify_relatives_list(true)
{
}


ComponentRelations::~ComponentRelations()
{
}


std::vector<std::string> ComponentRelations::build_dependents_list()
{
   std::string dependents_json_filename = "/Users/markoates/Repos/hexagon/documentation/dependents.json";
   Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader dependents_relations_loader(
      dependents_json_filename
   );
   return dependents_relations_loader.build_dependent_names_for_component_name(component.get_name());
}

std::vector<std::string> ComponentRelations::build_relatives_list()
{
   Blast::Project::ComponentRelativeLister relative_lister(&component);
   std::vector<std::string> result_component_names = relative_lister.list_component_relative_names();
   return result_component_names;
}

std::vector<std::string> ComponentRelations::build_dependencies_list()
{
   // TODO: test this functionality
   Blast::Project::ComponentDependencyLister dependency_lister(&component);
   std::vector<std::string> result_component_names = dependency_lister.list_component_dependency_names();
   return result_component_names;
}

std::string ComponentRelations::build_implicit_json_dependents_filename_for_project(std::string project_name)
{
   if (!(valid_project_name(&project_name)))
   {
      std::stringstream error_message;
      error_message << "[ComponentRelations::build_implicit_json_dependents_filename_for_project]: error: guard \"valid_project_name(&project_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ComponentRelations::build_implicit_json_dependents_filename_for_project: error: guard \"valid_project_name(&project_name)\" not met");
   }
   return "/Users/markoates/Repos/" + project_name + "/documentation/dependents.json";
}

bool ComponentRelations::valid_project_name(std::string* project_name)
{
   if (!(project_name))
   {
      std::stringstream error_message;
      error_message << "[ComponentRelations::valid_project_name]: error: guard \"project_name\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ComponentRelations::valid_project_name: error: guard \"project_name\" not met");
   }
   if (project_name->empty()) return false;
   for (char c : *project_name)
   {
      if (!std::isalnum(c) && c != '_' && c != '-')
      {
         return false;
      }
   }
   return true;
}


} // namespace ComponentRelationsNavigator
} // namespace Hexagon


