

#include <Hexagon/AdvancedComponentNavigator/ComponentSearcher.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <Blast/SimpleTextSearcher.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <Blast/SimpleTextSearcher.hpp>
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


std::vector<std::string> ComponentSearcher::convert_to_names(std::vector<Blast::Project::Component> components)
{
   std::vector<std::string> results;
   for (auto &element : components)
   {
      results.push_back(element.get_name());
      //results.push_back(Blast::Project::Component(element, project_root_directory));
   }
   return results;
}

std::vector<Blast::Project::Component> ComponentSearcher::convert_to_components(std::vector<std::string> names)
{
   std::vector<Blast::Project::Component> results;
   for (auto &element : names)
   {
      results.push_back(Blast::Project::Component(element, project_root_directory));
   }
   return results;
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
   std::vector<std::string> unfiltered_elements = {};

   // get list of elements
   unfiltered_elements = Blast::Project::ComponentLister(project_root_directory).components_sorted_by_most_recent();

   // filter list by search string
   std::vector<std::string> filtered_elements = Blast::SimpleTextSearcher(search_text, unfiltered_elements).results();

   // build (and return) components
   return convert_to_components(filtered_elements);
}

std::vector<Blast::Project::Component> ComponentSearcher::components()
{
   std::vector<Blast::Project::Component> result;
   return convert_to_components(component_names());
}
} // namespace AdvancedComponentNavigator
} // namespace Hexagon


