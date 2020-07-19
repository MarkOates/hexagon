

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
Blast::ShellCommandExecutorWithCallback executor(
      build_tracked_files_shell_command(),
      Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
return executor.execute();

}

std::vector<std::string> Stage::get_shell_response_lines()
{
Blast::ShellCommandExecutorWithCallback executor(
      build_tracked_files_shell_command(),
      Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
std::string command_output = executor.execute();
return Blast::StringSplitter(command_output, '\n').split();

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


