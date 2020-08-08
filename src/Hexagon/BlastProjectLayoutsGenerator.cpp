

#include <Hexagon/BlastProjectLayoutsGenerator.hpp>
#include <Blast/Project/ComponentLister.hpp>


namespace Hexagon
{


BlastProjectLayoutsGenerator::BlastProjectLayoutsGenerator(std::string project_directory)
   : project_directory(project_directory)
{
}


BlastProjectLayoutsGenerator::~BlastProjectLayoutsGenerator()
{
}


std::vector<Hexagon::Layout> BlastProjectLayoutsGenerator::generate()
{
std::vector<Hexagon::Layout> result;

Blast::Project::ComponentLister component_lister(project_directory);
std::vector<std::string> component_names = component_lister.components();

for (auto &component_name : component_names)
{
   result.push_back(Layout(component_name));
}

return result;

}
} // namespace Hexagon


