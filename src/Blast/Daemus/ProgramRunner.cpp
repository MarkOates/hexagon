

#include <Blast/Daemus/ProgramRunner.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Hexagon/System/Config.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>


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

build_command += project_directory + " && make focus)\"";
std::string output = execute_command(build_command);
return;

}

void ProgramRunner::run_with_block_after_command()
{
std::string rerun_command = "rerun --quiet -c -p \"**/*.{" \
   "rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}" \
   "\"";

std::string project_directory = "/Users/markoates/Repos/blast/";


//std::string COMMAND = "rerun --quiet -p \"**/*.{rb,js,tsx,coffee,css,scss,sass,erb,html,haml," \
//                      "ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}\" --restart";


std::vector<std::string> command_tokens;
command_tokens = {
  //"(cd ",
  //project_directory,
  //" && ",
  //rerun_command,
  //" \"(cd ",
  //project_directory,
  //" && make focus)\"",
  //COMMAND,
};

std::stringstream command;
for (auto &command_token : command_tokens)
{
   command << command_token << " ";
}

std::cout << "executing command \"" << command.str() << "\"" << std::endl;

std::string command_result_output = execute_command(command.str());
std::cout << command_result_output << std::endl;

std::cout << "finished command execution of \"" << command.str() << "\"" << std::endl;
return;

}
} // namespace Daemus
} // namespace Blast


