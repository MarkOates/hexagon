

#include <Hexagon/NewComponentMaker/NewComponentMaker.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace NewComponentMaker
{


NewComponentMaker::NewComponentMaker(std::string current_project_directory, std::string component_name)
   : current_project_directory(current_project_directory)
   , component_name(component_name)
   , shell_command_has_executed(false)
   , last_executed_shell_response("")
   , path_to_executable("~/Repos/blast/bin/programs/component_generator")
{
}


NewComponentMaker::~NewComponentMaker()
{
}


std::string NewComponentMaker::get_current_project_directory() const
{
   return current_project_directory;
}


std::string NewComponentMaker::get_shell_response()
{
   if (shell_command_has_executed) return last_executed_shell_response;
   Blast::ShellCommandExecutorWithCallback executor(
         build_shell_command(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
   last_executed_shell_response = executor.execute();
   return last_executed_shell_response;
}

std::vector<std::string> NewComponentMaker::get_shell_response_lines()
{
   return Blast::StringSplitter(get_shell_response(), '\n').split();
}

std::string NewComponentMaker::build_shell_command()
{
   std::stringstream commit_everything_shell_command;
   commit_everything_shell_command << "("
                                   << "cd " << current_project_directory
                                   << " && "
                                   << path_to_executable << " " << component_name
                                   << ")";

   return commit_everything_shell_command.str();
}
} // namespace NewComponentMaker
} // namespace Hexagon


