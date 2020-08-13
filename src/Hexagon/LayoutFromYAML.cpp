

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

Hexagon::Layout result(concept_name);

return result;

}
} // namespace Hexagon


