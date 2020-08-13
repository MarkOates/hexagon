#pragma once


#include <Hexagon/Layout.hpp>
#include <string>


namespace Hexagon
{
   class LayoutFromYAML
   {
   private:
      std::string yaml;

   public:
      LayoutFromYAML(std::string yaml="# empty");
      ~LayoutFromYAML();


   Hexagon::Layout load();
   };
}



