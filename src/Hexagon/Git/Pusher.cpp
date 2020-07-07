

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

std::string Pusher::push()
{
Blast::ShellCommandExecutorWithCallback executor(get_push_shell_command());
return executor.execute();

}
} // namespace Git
} // namespace Hexagon


