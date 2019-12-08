

#include <Hexagon/ComponentNavigator/List.hpp>
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
} // namespace ComponentNavigator
} // namespace Hexagon


