

#include <Hexagon/Git/Staged.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <sstream>


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


std::string Staged::get_current_project_directory() const
{
   return current_project_directory;
}


std::vector<std::string> Staged::get_shell_response()
{
   Blast::ShellCommandExecutorWithCallback executor(
         build_staged_files_shell_command(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
   std::string command_output = executor.execute();
   return Blast::StringSplitter(command_output, '\n').split();
}

std::string Staged::build_staged_files_shell_command()
{
   std::stringstream commit_everything_shell_command;
   commit_everything_shell_command << "(cd " << current_project_directory << " && git diff --staged --name-only)";
   return commit_everything_shell_command.str();
}


} // namespace Git
} // namespace Hexagon


