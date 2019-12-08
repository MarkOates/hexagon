

#include <Hexagon/ComponentNavigator/List.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <Blast/Project/ComponentLister.hpp>


namespace Hexagon
{
namespace ComponentNavigator
{


List::List(std::string project_root_directory)
   : project_root_directory(project_root_directory)
{
}


List::~List()
{
}


std::vector<std::string> List::component_names()
{
return Blast::Project::ComponentLister(project_root_directory).components();

}

std::vector<Blast::Project::Component> List::components()
{
std::vector<Blast::Project::Component> result;
std::vector<std::string> component_names = Blast::Project::ComponentLister(project_root_directory).components();
for (auto &component_name : component_names)
{
   result.push_back(Blast::Project::Component(component_name, project_root_directory));
}
return result;

}
} // namespace ComponentNavigator
} // namespace Hexagon


