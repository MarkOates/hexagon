

#include <Hexagon/BuildSystem/Controller.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Hexagon
{
namespace BuildSystem
{


Controller::Controller()
{
}


Controller::~Controller()
{
}


std::string Controller::create()
{
   // run a simple build command
   std::string directory = "/Users/markoates/Repos/hexagon";
   std::string build_command = "g++ -std=c++17 tests/fixtures/source_files/a_program.cpp -o ./tmp/a_program";

   std::stringstream full_shell_command;
   full_shell_command << "(cd " << directory << " && " << build_command << " && ./tmp/a_program)";
   Blast::ShellCommandExecutorWithCallback executor =
      Blast::ShellCommandExecutorWithCallback(
         full_shell_command.str(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );

   std::string command_result = executor.execute();

   // collect the binary artifact
   // copy the binary artifact to a destination
   return command_result;
}
} // namespace BuildSystem
} // namespace Hexagon


