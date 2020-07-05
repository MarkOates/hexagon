

#include <Blast/Daemus/Daemus.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <stdexcept>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <iostream>
#include <unistd.h>


namespace Blast
{
namespace Daemus
{


Daemus::Daemus(std::string quintessence_build_executable)
   : quintessence_build_executable(quintessence_build_executable)
{
}


Daemus::~Daemus()
{
}


void Daemus::run_full_rebuild()
{
std::string full_rebuild_command = "make clean && make programs && make && make clean && make programs && make";
execute_command(full_rebuild_command);

}

void Daemus::run_simple_echo_command()
{
execute_command("printf \"hello\"");
}

void Daemus::run_simple_sleep_command()
{
execute_command("echo \"sleeping\"; sleep 0.5; echo \"done\"");
}

void Daemus::run_build_quintessence_file(std::string quintessence_filename)
{
if (!(Blast::FileExistenceChecker(quintessence_build_executable).exists()))
   {
      std::stringstream error_message;
      error_message << "Daemus" << "::" << "run_build_quintessence_file" << ": error: " << "guard \"Blast::FileExistenceChecker(quintessence_build_executable).exists()\" not met";
      throw std::runtime_error(error_message.str());
   }
if (!(Blast::FileExistenceChecker(quintessence_filename).exists()))
   {
      std::stringstream error_message;
      error_message << "Daemus" << "::" << "run_build_quintessence_file" << ": error: " << "guard \"Blast::FileExistenceChecker(quintessence_filename).exists()\" not met";
      throw std::runtime_error(error_message.str());
   }
return;

}

std::string Daemus::execute_command(std::string command)
{
Blast::ShellCommandExecutorWithCallback shell_command_executor(
   command,
   Blast::ShellCommandExecutorWithCallback::simple_cout_callback
   //Blast::ShellCommandExecutorWithCallback::simple_silent_callback
);
return shell_command_executor.execute();

}

void Daemus::output_pid()
{
std::cout << "pid: " << getpid() << std::endl;
return;

}
} // namespace Daemus
} // namespace Blast


