

#include <Hexagon/ComponentDependencies.hpp>




namespace Hexagon
{


ComponentDependencies::ComponentDependencies(std::string component_name)
   : component_name(component_name)
   , dependencies({})
{
}


ComponentDependencies::~ComponentDependencies()
{
}


std::set<std::string> ComponentDependencies::get_dependencies() const
{
   return dependencies;
}


std::string ComponentDependencies::generate_dependency_filename()
{
   return "deps/" + component_name + ".d";
}


} // namespace Hexagon


