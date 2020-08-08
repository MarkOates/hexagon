#pragma once


#include <Hexagon/Layout.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class BlastProjectLayoutsGenerator
   {
   private:
      std::string project_directory;

   public:
      BlastProjectLayoutsGenerator(std::string project_directory="Users/markoates/Repos/hexagon/");
      ~BlastProjectLayoutsGenerator();


   std::vector<Hexagon::Layout> generate();
   Hexagon::Layout build_appropriate_layout_for_component(std::string component_name="UnnamedComponent");
   };
}



