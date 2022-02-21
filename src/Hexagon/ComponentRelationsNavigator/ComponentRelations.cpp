

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>
#include <Hexagon/ComponentRelationsNavigator/DocumentationDependentsJSONLoader.hpp>
#include <Blast/Project/ComponentRelativeLister.hpp>


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
   Hexagon::ComponentRelationsNavigator::DocumentationDependentsJSONLoader dependents_relations_loader;
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
   // TODO: fill out this list
   return { "Not/Yet/Implemented" };
}
} // namespace ComponentRelationsNavigator
} // namespace Hexagon


