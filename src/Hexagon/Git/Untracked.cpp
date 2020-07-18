

#include <Hexagon/Git/Untracked.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Hexagon
{
namespace Git
{


Untracked::Untracked(std::string current_project_directory)
   : current_project_directory(current_project_directory)
{
}


Untracked::~Untracked()
{
}


std::string Untracked::get_current_project_directory()
{
   return current_project_directory;
}


std::string Untracked::get_shell_response()
{
Blast::ShellCommandExecutorWithCallback executor(
      build_tracked_files_shell_command(),
      Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
return executor.execute();

}

std::string Untracked::build_tracked_files_shell_command()
{
std::stringstream commit_everything_shell_command;
commit_everything_shell_command << "("
                                << "cd " << current_project_directory
                                << " && "
                                << "git ls-files --others --exclude-standard"
                                << ")";

return commit_everything_shell_command.str();

}
} // namespace Git
} // namespace Hexagon


