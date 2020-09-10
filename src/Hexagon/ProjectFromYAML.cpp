

#include <Hexagon/ProjectFromYAML.hpp>
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
Hexagon::Project project;

std::vector<std::tuple<std::string, Hexagon::Layout>> layouts = {
   { "label", Hexagon::Layout("Fancy/ConceptName") },
};

project.set_layouts(layouts);

return project;

}
} // namespace Hexagon


