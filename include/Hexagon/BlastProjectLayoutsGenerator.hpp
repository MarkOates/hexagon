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
   std::string component_generate_header_filename(std::string component_name="UnnamedComponent");
   std::string component_generate_source_filename(std::string component_name="UnnamedComponent");
   std::string component_generate_test_filename(std::string component_name="UnnamedComponent");
   };
}



