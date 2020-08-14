

#include <Hexagon/ProjectFromYAML.hpp>
#include <Hexagon/Project.hpp>
#include <yaml-cpp/yaml.h>


namespace Hexagon
{


ProjectFromYAML::ProjectFromYAML(std::string source_yaml)
   : source_yaml(source_yaml)
{
}


ProjectFromYAML::~ProjectFromYAML()
{
}


Hexagon::Project ProjectFromYAML::load()
{
YAML::Node node = YAML::Load(source_yaml);

return {};

}
} // namespace Hexagon


