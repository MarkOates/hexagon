

#include <Hexagon/NewComponentMaker/Stage.hpp>
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


Stage::Stage(std::string current_project_directory)
   : current_project_directory(current_project_directory)
   , shell_command_has_executed(false)
   , last_executed_shell_response("")
{
}


Stage::~Stage()
{
}


std::string Stage::get_current_project_directory()
{
   return current_project_directory;
}


std::string Stage::get_shell_response()
{
if (shell_command_has_executed) return last_executed_shell_response;
Blast::ShellCommandExecutorWithCallback executor(
      build_tracked_files_shell_command(),
      Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
last_executed_shell_response = executor.execute();
return last_executed_shell_response;

}

std::vector<std::string> Stage::get_shell_response_lines()
{
return Blast::StringSplitter(get_shell_response(), '\n').split();

}

std::string Stage::build_tracked_files_shell_command()
{
std::stringstream commit_everything_shell_command;
commit_everything_shell_command << "("
                                << "cd " << current_project_directory
                                << " && "
                                << "git diff --name-only"
                                << ")";

return commit_everything_shell_command.str();

}
} // namespace NewComponentMaker
} // namespace Hexagon


