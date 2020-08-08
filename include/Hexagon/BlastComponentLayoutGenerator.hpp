#pragma once


#include <Hexagon/Layout.hpp>
#include <string>


namespace Hexagon
{
   class BlastComponentLayoutGenerator
   {
   private:
      std::string project_directory;
      std::string component_name;
      int code_editor_width;
      int code_editor_height;

   public:
      BlastComponentLayoutGenerator(std::string project_directory="Users/markoates/Repos/hexagon/", std::string component_name="UnnamedComponent");
      ~BlastComponentLayoutGenerator();


   Hexagon::Layout generate();
   std::string component_generate_header_filename();
   std::string component_generate_source_filename();
   std::string component_generate_test_filename();
   std::string component_generate_quintessence_filename();
   };
}



