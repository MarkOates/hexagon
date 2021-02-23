

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
   std::string build_command = "g++ -std=c++17 tests/fixtures/source_files/a_program.cpp";

   std::stringstream shell_command;
   shell_command << "(cd " << directory << " && " << build_command << " && echo )";
   Blast::ShellCommandExecutorWithCallback executor =
      Blast::ShellCommandExecutorWithCallback(
         shell_command.str(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );

   std::string command_result = executor.execute();

   // collect the binary artifact
   // copy the binary artifact to a destination
   return command_result;
}
} // namespace BuildSystem
} // namespace Hexagon


