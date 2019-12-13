

#include <Hexagon/Testing/ComponentTestRunner.hpp>
#include <Blast/Project/Component.hpp>


namespace Hexagon
{
namespace Testing
{


ComponentTestRunner::ComponentTestRunner()
   : project_root("/Users/markoates/Repos/hexagon/")
   , component_name("Hexagon/UnnamedComponent")
{
}


ComponentTestRunner::~ComponentTestRunner()
{
}


std::string ComponentTestRunner::get_project_root()
{
   return project_root;
}


std::string ComponentTestRunner::get_component_name()
{
   return component_name;
}


std::string ComponentTestRunner::generate_make_run_test_command()
{
Blast::Project::Component component(get_component_name(), get_project_root());
std::string full_path_test_filename = component.generate_full_path_test_binary_filename();
std::string result
  = std::string("(")
  + "cd "
  + project_root
  + " && make "
  + full_path_test_filename
  + ")"
  + "; "
  + full_path_test_filename
  + " && "
  + "echo FINAL_EXIT_CODE:$?"
  ;
return result;

}

std::string ComponentTestRunner::run()
{
return "Hello World!";
}
} // namespace Testing
} // namespace Hexagon


