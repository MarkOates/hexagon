

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

YAML::Node layouts_node = node["layouts"];
std::vector<std::tuple<std::string, Hexagon::Layout>> layouts;
for (std::size_t i=0;i<layouts_node.size();i++)
{
   std::string layout_label = "label";
   YAML::Node layout_node = layouts_node[i];
   Hexagon::Layout layout = Hexagon::LayoutFromYAML(layout_node).load();

   layouts.push_back({layout_label, layout});
}

layouts = {
   { "label", Hexagon::Layout("Fancy/ConceptName") },
};

project.set_layouts(layouts);

return project;

}
} // namespace Hexagon


