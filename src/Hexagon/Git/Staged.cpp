

#include <Hexagon/Git/Staged.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Hexagon
{
namespace Git
{


Staged::Staged(std::string current_project_directory)
   : current_project_directory(current_project_directory)
{
}


Staged::~Staged()
{
}


std::string Staged::get_staged_response()
{
Blast::ShellCommandExecutorWithCallback executor(
      build_staged_files_shell_command(),
      Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
return executor.execute();

}

std::string Staged::build_staged_files_shell_command()
{
std::stringstream commit_everything_shell_command;
commit_everything_shell_command << "(cd " << current_project_directory << " && git diff --staged --name-only)";
return commit_everything_shell_command.str();

}
} // namespace Git
} // namespace Hexagon


