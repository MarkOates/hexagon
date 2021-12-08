

#include <Hexagon/ComponentRelationsNavigator/ComponentRelations.hpp>



namespace Hexagon
{
namespace ComponentRelationsNavigator
{


ComponentRelations::ComponentRelations()
   : component("")
{
}


ComponentRelations::~ComponentRelations()
{
}


std::vector<Blast::Project::Component> ComponentRelations::build_dependents()
{
   return {};
}

std::vector<Blast::Project::Component> ComponentRelations::build_relatives()
{
   return {};
}

std::vector<Blast::Project::Component> ComponentRelations::build_dependencies()
{
   return {};
}
} // namespace ComponentRelationsNavigator
} // namespace Hexagon


