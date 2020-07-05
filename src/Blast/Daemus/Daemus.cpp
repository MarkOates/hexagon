

#include <Blast/Daemus/Daemus.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <iostream>
#include <unistd.h>


namespace Blast
{
namespace Daemus
{


Daemus::Daemus()
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


