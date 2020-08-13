

#include <Hexagon/LayoutFromYAML.hpp>
#include <yaml-cpp/yaml.h>
#include <Hexagon/Layout.hpp>


namespace Hexagon
{


LayoutFromYAML::LayoutFromYAML(std::string source_yaml)
   : source_yaml(source_yaml)
{
}


LayoutFromYAML::~LayoutFromYAML()
{
}


Hexagon::Layout LayoutFromYAML::load()
{
// https://github.com/jbeder/yaml-cpp/wiki/Tutorial


// create the root node
YAML::Node node = YAML::Load(source_yaml);


// parse concept name
std::string concept_name = node["name"].as<std::string>();

YAML::Node files_node = node["files"];


// parse files
std::vector<std::tuple<std::string, std::string, placement3d>> result_files = {};
for (std::size_t i=0;i<files_node.size();i++)
{
}

std::string daemus_command = ""; // node["daemus"].as<std::string>();


// build the object
Hexagon::Layout result(concept_name, result_files, daemus_command);

return result;

}
} // namespace Hexagon


