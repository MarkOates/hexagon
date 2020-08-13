

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

YAML::Node node = YAML::Load(source_yaml);

std::string concept_name = node["name"].as<std::string>();

YAML::Node files_node = node["files"];
std::vector<std::tuple<std::string, std::string, placement3d>> files = {};

Hexagon::Layout result(concept_name);

return result;

}
} // namespace Hexagon


