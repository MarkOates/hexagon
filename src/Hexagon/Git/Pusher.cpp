

#include <Hexagon/Git/Pusher.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Hexagon
{
namespace Git
{


Pusher::Pusher(std::string current_project_directory)
   : current_project_directory(current_project_directory)
{
}


Pusher::~Pusher()
{
}


std::string Pusher::get_push_shell_command()
{
   std::stringstream commit_everything_shell_command;
   commit_everything_shell_command
      << "(cd " << current_project_directory << " && git push)"
      << "; echo \"RETURN_CODE($?)\"";
   return commit_everything_shell_command.str();
}

void Pusher::validate_result_or_throw_error_on_failure(std::string response)
{
   std::string capture_string_for_destination_repo_not_defined_error = "fatal: No configured push destination.";
   return;
}

std::string Pusher::push()
{
   Blast::ShellCommandExecutorWithCallback executor(get_push_shell_command());
   std::string response = executor.execute();
   validate_result_or_throw_error_on_failure(response);
   return response;
}
} // namespace Git
} // namespace Hexagon


