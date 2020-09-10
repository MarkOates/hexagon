#pragma once


#include <Hexagon/Layout.hpp>
#include <string>
#include <yaml-cpp/yaml.h>


namespace Hexagon
{
   class LayoutFromYAML
   {
   private:
      std::string source_yaml;
      YAML::Node yaml_node;

   public:
      LayoutFromYAML(std::string source_yaml="# empty", YAML::Node yaml_node={});
      ~LayoutFromYAML();


   Hexagon::Layout load();
   };
}



