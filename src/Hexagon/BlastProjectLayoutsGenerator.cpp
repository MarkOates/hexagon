

#include <Hexagon/BlastProjectLayoutsGenerator.hpp>
#include <Blast/Project/ComponentLister.hpp>
#include <Blast/Project/Component.hpp>
#include <iostream>


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

void BlastProjectLayoutsGenerator::build_appropriate_layout_for_component(std::string component_name)
{
Blast::Project::Component component(component_name, project_directory);

if (component.has_only_source_and_header())
{
   //return create_three_split_from_last_component_navigator_selection();
}
else if (component.has_quintessence() || component.has_test())
{
   //return attempt_to_create_stage_from_last_component_navigator_selection();
}
else
{
   std::cout << "cannot build_appropriate_layout_for_component "
             << "because the component \"" << component.get_name() << "\" "
             << "neither has a header/source combo nor a quintessence or test file."
             << std::endl;
   return;
}
return;

}
} // namespace Hexagon


