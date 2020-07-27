

#include <Blast/Daemus/ProgramRunner.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Hexagon/System/Config.hpp>


namespace Blast
{
namespace Daemus
{


ProgramRunner::ProgramRunner()
{
}


ProgramRunner::~ProgramRunner()
{
}


std::string ProgramRunner::execute_command(std::string command)
{
Blast::ShellCommandExecutorWithCallback shell_command_executor(
   command,
   Blast::ShellCommandExecutorWithCallback::simple_cout_callback
   //Blast::ShellCommandExecutorWithCallback::simple_silent_callback
);
return shell_command_executor.execute();

}

void ProgramRunner::run()
{
run_with_rerun();
return;

}

void ProgramRunner::run_with_rerun()
{
al_init();
Hexagon::System::Config hexagon_config;
hexagon_config.initialize();

std::string project_directory = hexagon_config.get_default_navigator_directory();
std::string actual_command_to_execute_in_project_directory = "make focus";

std::string build_command = "rerun" \
  " " \
  "-c" \
  " " \
  "--background" \
  " " \
  "--ignore \"**/bin/programs/data/tmp/*\"" \
  " " \
  "-p \"**/*.{rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}\"" \
  " " \
  "\"(cd ";

build_command += project_directory + " && " + actual_command_to_execute_in_project_directory + ")\"";
std::string output = execute_command(build_command);
return;

}
} // namespace Daemus
} // namespace Blast


