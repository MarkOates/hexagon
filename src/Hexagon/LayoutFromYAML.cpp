

#include <Hexagon/LayoutFromYAML.hpp>
#include <yaml-cpp/yaml.h>
#include <Hexagon/Layout.hpp>
#include <iostream>


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


// pre-sanitize
//
// Certain strings can cause parsing to stall.  So far, a string "{# ke\ny{:" has been identified
// as causing this program halt, and can be resolved by ensuring a newline is present at the end.
// This is not the right approach (the library should not stall in the first place) so hopefully
// this is good enough to catch the edge case and not cause unexplained differences in parsing data
// length.
//
// Here is an issue describing it: https://github.com/jbeder/yaml-cpp/issues/938
if (source_yaml.empty()) return {};
else if (source_yaml.back() != '\n') source_yaml.append("\n");


// create the root node
YAML::Node node;
try
{
   node = YAML::Load(source_yaml);
}
catch (std::exception &e)
{
   std::stringstream error_message;
   error_message << "foobar" << std::endl;
   throw std::runtime_error(error_message.str());
}


// parse concept name
std::string concept_name;
if (node["name"])
{
   concept_name = node["name"].as<std::string>();
}


// parse files
YAML::Node files_node = node["files"];
std::vector<std::tuple<std::string, std::string, placement3d>> result_files = {};
for (std::size_t i=0;i<files_node.size();i++)
{
   YAML::Node file_node = files_node[i];
   std::string filename = file_node["filename"].as<std::string>();
   std::string file_type = file_node["file_type"].as<std::string>();
   placement3d result_placement;

   if (file_node["placement"])
   {
      YAML::Node placement_node = file_node["placement"];
      float x = placement_node["x"].as<float>();
      float y = placement_node["y"].as<float>();
      float z = placement_node["z"].as<float>();

      result_placement = { x, y, z };
   }

   std::tuple<std::string, std::string, placement3d> file = { filename, file_type, result_placement };
   result_files.push_back(file);
}


// parse daemus command
std::string daemus_command;
if (node["daemus_command"])
{
   daemus_command = node["daemus_command"].as<std::string>();
}


// build the object
Hexagon::Layout result(concept_name, result_files, daemus_command);


return result;

}
} // namespace Hexagon


