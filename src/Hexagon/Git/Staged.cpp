

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


std::string Staged::get_commit_everything_shell_command()
{
std::stringstream commit_everything_shell_command;
commit_everything_shell_command << "(cd " << current_project_directory << " && git diff --staged)";
return commit_everything_shell_command.str();

}

std::string Staged::get_staged_response()
{
Blast::ShellCommandExecutorWithCallback executor(get_commit_everything_shell_command());
return executor.execute();

}
} // namespace Git
} // namespace Hexagon


