

#include <Hexagon/LayoutFromYAML.hpp>
#include <yaml-cpp/yaml.h>
#include <Hexagon/Layout.hpp>


namespace Hexagon
{


LayoutFromYAML::LayoutFromYAML(std::string yaml)
   : yaml(yaml)
{
}


LayoutFromYAML::~LayoutFromYAML()
{
}


Hexagon::Layout LayoutFromYAML::load()
{
Hexagon::Layout result;
return result;

}
} // namespace Hexagon


