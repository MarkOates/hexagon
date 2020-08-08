#pragma once


#include <Hexagon/Layout.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   class BlastComponentLayoutGenerator
   {
   private:
      std::string project_directory;
      int code_editor_width;
      int code_editor_height;

   public:
      BlastComponentLayoutGenerator(std::string project_directory="Users/markoates/Repos/hexagon/");
      ~BlastComponentLayoutGenerator();


   std::vector<Hexagon::Layout> generate();
   Hexagon::Layout build_appropriate_layout_for_component(std::string component_name="UnnamedComponent");
   std::string component_generate_header_filename(std::string component_name="UnnamedComponent");
   std::string component_generate_source_filename(std::string component_name="UnnamedComponent");
   std::string component_generate_test_filename(std::string component_name="UnnamedComponent");
   std::string component_generate_quintessence_filename(std::string component_name="UnnamedComponent");
   };
}



