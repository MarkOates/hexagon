#pragma once


#include <Hexagon/Layout.hpp>
#include <yaml-cpp/yaml.h>


namespace Hexagon
{
   class LayoutFromYAML
   {
   private:
      YAML::Node root_node;

   public:
      LayoutFromYAML(YAML::Node root_node={});
      ~LayoutFromYAML();


   Hexagon::Layout load();
   };
}



