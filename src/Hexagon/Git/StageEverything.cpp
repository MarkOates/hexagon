

#include <Hexagon/Git/StageEverything.hpp>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


namespace Hexagon
{
namespace Git
{


StageEverything::StageEverything(std::string current_project_directory)
   : current_project_directory(current_project_directory)
{
}


StageEverything::~StageEverything()
{
}


bool StageEverything::stage_everything()
{
std::stringstream stage_everything_shell_command;
stage_everything_shell_command << "(cd " << current_project_directory << " && git add .)";
Blast::ShellCommandExecutorWithCallback executor(stage_everything_shell_command.str());
executor.execute();
return true;

}
} // namespace Git
} // namespace Hexagon


