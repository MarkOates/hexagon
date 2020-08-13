#pragma once


#include <Hexagon/Layout.hpp>
#include <string>


namespace Hexagon
{
   class LayoutFromYAML
   {
   private:
      std::string source_yaml;

   public:
      LayoutFromYAML(std::string source_yaml="# empty");
      ~LayoutFromYAML();


   Hexagon::Layout load();
   };
}



