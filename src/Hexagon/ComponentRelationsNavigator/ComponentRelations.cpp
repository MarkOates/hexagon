

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>
#include <Blast/Project/ComponentRelativeLister.hpp>


namespace Hexagon
{
namespace ComponentRelationsNavigator
{


ComponentRelations::ComponentRelations(Blast::Project::Component component)
   : component(component)
{
}


ComponentRelations::~ComponentRelations()
{
}


std::vector<std::string> ComponentRelations::build_dependents_list()
{
   return {};
}

std::vector<std::string> ComponentRelations::build_relatives_list()
{
   Blast::Project::ComponentRelativeLister relative_lister(&component);
   std::vector<std::string> result_component_names = relative_lister.list_component_relative_names();
   return result_component_names;
}

std::vector<std::string> ComponentRelations::build_dependencies_list()
{
   return {};
}
} // namespace ComponentRelationsNavigator
} // namespace Hexagon


