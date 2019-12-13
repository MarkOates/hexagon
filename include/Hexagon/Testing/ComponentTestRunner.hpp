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
         ComponentTestRunner();
         ~ComponentTestRunner();


         std::string get_project_root();
         std::string get_component_name();
      std::string generate_make_test_command();
      std::string generate_run_test_command();
      std::string run();
      };
   }
}



