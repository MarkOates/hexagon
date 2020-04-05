

#include <Blast/Daemus/ProgramRunner.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
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


std::string ProgramRunner::__replace(std::string str, std::string from, std::string to)
{
size_t start_pos = 0;
while((start_pos = str.find(from, start_pos)) != std::string::npos) {
   str.replace(start_pos, from.length(), to);
   start_pos += to.length();
}
return str;

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

void ProgramRunner::block_execution_with_rerun_pause()
{
std::string rerun_command = "rerun --quiet -c -p \"**/*.{" \
   "rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}" \
   "\"";
std::string project_directory = "/Users/markoates/Repos/blast/";
std::vector<std::string> command_tokens;
command_tokens = {
  //"(cd ",
  //project_directory,
  //" && ",
  rerun_command,
  " \"(cd ",
     project_directory,
     " && exit)\"",
};

std::stringstream command;
for (auto &command_token : command_tokens)
{
   command << command_token << " ";
}

execute_command(command.str());
return;

}

void ProgramRunner::run_full_rebuild()
{
std::string full_rebuild_command = "make clean && make programs && make && make clean && make programs && make";
execute_command(full_rebuild_command);

}

void ProgramRunner::run()
{
//while(true)
{
   std::string build_command = "rerun" \
     " " \
     "-c" \
     " " \
     "--background" \
     " " \
     "-p \"**/*.{rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}\"" \
     " " \
     "\"(cd /Users/markoates/Repos/blast/ && make focus)\"";
   std::string output = execute_command(build_command);
   //std::cout << output << std::endl;
   //run_with_block_after_command();
}
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
//block_execution_with_rerun_pause();
return;

}
} // namespace Daemus
} // namespace Blast


