

#include <Hexagon/ProjectFromYAML.hpp>
#include <Hexagon/LayoutFromYAML.hpp>
#include <Hexagon/Project.hpp>
#include <yaml-cpp/yaml.h>


namespace Hexagon
{


ProjectFromYAML::ProjectFromYAML(std::string name, std::string source_yaml)
   : name(name)
   , source_yaml(source_yaml)
{
}


ProjectFromYAML::~ProjectFromYAML()
{
}


Hexagon::Project ProjectFromYAML::load()
{
YAML::Node node = YAML::Load(source_yaml);
Hexagon::Project project(name);

YAML::Node layouts_node = node["components"];
std::vector<std::tuple<std::string, Hexagon::Layout>> layouts;
for (std::size_t i=0;i<layouts_node.size();i++)
{
   YAML::Node layout_node = layouts_node[i];
   Hexagon::Layout layout = Hexagon::LayoutFromYAML(layout_node).load();
   std::string layout_label = layout.get_concept_name();

   layouts.push_back({layout_label, layout});
}

project.set_layouts(layouts);

return project;

}
} // namespace Hexagon


