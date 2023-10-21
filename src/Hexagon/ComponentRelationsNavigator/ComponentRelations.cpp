

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>

#include <Blast/Project/ComponentDependencyLister.hpp>
#include <Blast/Project/ComponentRelativeLister.hpp>
#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>
#include <Hexagon/DependencyManager.hpp>
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
   { // Strategy 1: Use Dependencies JSON from documentation, and reverse it
      //std::string dependents_json_filename = "/Users/markoates/Repos/hexagon/documentation/dependents.json";
      std::string dependents_json_filename =
         build_implicit_json_dependents_filename_for_project(component.get_project_root());
      Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader dependents_relations_loader(
         dependents_json_filename
      );
      return dependents_relations_loader.build_dependent_names_for_component_name(component.get_name());
   }
   /*
   { // Strategy 2: Ues Hexagon::DependencyManager, which reads from /.deps folder
      std::string component_name = component.get_name();
      Hexagon::DependencyManager dependency_manager(component.get_project_root() + "/");
      //Hexagon::DependencyManager dependency_manager(TEST_FIXTURE_PROJECT_FOLDER);
      dependency_manager.load_from_source_tree();
      std::map<std::string, std::set<std::string>> dependents = dependency_manager.get_dependents();
      bool component_exists_in_deps_listing = dependents.count(component.get_name()) == 0;
      if (!component_exists_in_deps_listing) return std::vector<std::string>({"not-found"});
      // convert our set to a vector
      std::vector<std::string> result;
      for (auto &element : dependents[component.get_name()])
      {
         result.push_back(element);
      }
      return result; //dependents[component.get_name()];
   }
   */
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

std::string ComponentRelations::build_implicit_json_dependents_filename_for_project(std::string project_root)
{
   if (!(valid_project_root(&project_root)))
   {
      std::stringstream error_message;
      error_message << "[ComponentRelations::build_implicit_json_dependents_filename_for_project]: error: guard \"valid_project_root(&project_root)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ComponentRelations::build_implicit_json_dependents_filename_for_project: error: guard \"valid_project_root(&project_root)\" not met");
   }
   return project_root + "/documentation/dependents.json";
}

bool ComponentRelations::valid_project_root(std::string* project_root)
{
   if (!(project_root))
   {
      std::stringstream error_message;
      error_message << "[ComponentRelations::valid_project_root]: error: guard \"project_root\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ComponentRelations::valid_project_root: error: guard \"project_root\" not met");
   }
   std::string expected_prefix = "/Users/markoates/Repos/";
   bool has_valid_prefixed_path = (project_root->compare(0, expected_prefix.length(), expected_prefix) == 0);
   if (!has_valid_prefixed_path) return false;

   if (project_root->empty()) return false;
   for (char c : *project_root)
   {
      if (!std::isalnum(c) && c != '_' && c != '-' && c != '/')
      {
         return false;
      }
   }
   return true;
}


} // namespace ComponentRelationsNavigator
} // namespace Hexagon


