#pragma once


#include <string>


namespace Hexagon
{
   namespace Testing
   {
      class ComponentTestRunner
      {
      private:
         std::string project_root;
         std::string component_name;

      public:
         ComponentTestRunner(std::string project_root="/Users/markoates/Repos/hexagon/", std::string component_name="Hexagon/UnnamedComponent");
         ~ComponentTestRunner();

         std::string get_project_root();
         std::string get_component_name();
         std::string generate_make_run_test_command();
         std::string run();
      };
   }
}



