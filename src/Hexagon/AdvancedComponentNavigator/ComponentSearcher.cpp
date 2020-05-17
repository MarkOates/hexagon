

#include <Hexagon/AdvancedComponentNavigator/ComponentSearcher.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <Blast/SimpleTextSearcher.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <Blast/Project/ComponentLister.hpp>


namespace Hexagon
{
namespace AdvancedComponentNavigator
{


ComponentSearcher::ComponentSearcher(std::string project_root_directory, std::string search_text)
   : project_root_directory(project_root_directory)
   , search_text(search_text)
{
}


ComponentSearcher::~ComponentSearcher()
{
}


std::vector<std::string> ComponentSearcher::component_names()
{
std::vector<std::string> result_names = {};
std::vector<std::string> elements = Blast::Project::ComponentLister(project_root_directory).components();
if (search_text.empty()) return elements;
Blast::SimpleTextSearcher searcher(search_text, elements);
return searcher.results();

}

std::vector<Blast::Project::Component> ComponentSearcher::components_sorted_by_most_recent()
{
std::vector<Blast::Project::Component> result;
std::vector<std::string> component_names = {};
component_names = Blast::Project::ComponentLister(project_root_directory).components_sorted_by_most_recent();
for (auto &component_name : component_names)
{
   result.push_back(Blast::Project::Component(component_name, project_root_directory));
}
return result;

}

std::vector<Blast::Project::Component> ComponentSearcher::components()
{
std::vector<Blast::Project::Component> result;
std::vector<std::string> component_names = Blast::Project::ComponentLister(project_root_directory).components();
for (auto &component_name : component_names)
{
   result.push_back(Blast::Project::Component(component_name, project_root_directory));
}
return result;

}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


