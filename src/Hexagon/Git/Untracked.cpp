

#include <Hexagon/Git/Untracked.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <sstream>


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


std::string Untracked::get_current_project_directory() const
{
   return current_project_directory;
}


std::vector<std::string> Untracked::get_shell_response()
{
   Blast::ShellCommandExecutorWithCallback executor(
         build_tracked_files_shell_command(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
   std::string command_output = executor.execute();
   return Blast::StringSplitter(command_output, '\n').split();
}

std::string Untracked::build_tracked_files_shell_command()
{
   std::stringstream shell_command;
   shell_command << "("
                 << "cd " << current_project_directory
                 << " && "
                 << "git ls-files --others --exclude-standard"
                 << ")";

   return shell_command.str();
}


} // namespace Git
} // namespace Hexagon


