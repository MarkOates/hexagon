

#include <Hexagon/Git/Modified.hpp>

#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Blast/StringSplitter.hpp>
#include <sstream>


namespace Hexagon
{
namespace Git
{


Modified::Modified(std::string current_project_directory)
   : current_project_directory(current_project_directory)
{
}


Modified::~Modified()
{
}


std::string Modified::get_current_project_directory() const
{
   return current_project_directory;
}


std::vector<std::string> Modified::get_shell_response()
{
   Blast::ShellCommandExecutorWithCallback executor(
         build_tracked_files_shell_command(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
   std::string command_output = executor.execute();
   return Blast::StringSplitter(command_output, '\n').split();
}

std::string Modified::build_tracked_files_shell_command()
{
   std::stringstream commit_everything_shell_command;
   commit_everything_shell_command << "("
                                   << "cd " << current_project_directory
                                   << " && "
                                   << "git diff --name-only"
                                   << ")";

   return commit_everything_shell_command.str();
}


} // namespace Git
} // namespace Hexagon


