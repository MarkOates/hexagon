

#include <Hexagon/CppCompiler.hpp>


#include <Blast/ShellCommandExecutor.hpp>
#include <iostream>
#include <sstream>


namespace CppCompiler
{
   CompileRunner::CompileRunner(std::string filename)
      : filename(filename)
      , command_string(MAKE_COMMAND_ONLY_STDERR)
   {}


   CompileRunner::~CompileRunner()
   {}


   std::string CompileRunner::run()
   {
      //std::stringstream make_command_string;
      //make_command_string << "make 2>&1"; // should be "make" by default
      std::string cmd = "cd /Users/markoates/Repos/hexagon && " + command_string;
      Blast::ShellCommandExecutor shell_command_executor(cmd);
      std::string output = shell_command_executor.execute();
      //std::cout << output << std::endl;
      return output;
   }
}


const std::string CppCompiler::CompileRunner::MAKE_COMMAND_ONLY_STDOUT = "make";
const std::string CppCompiler::CompileRunner::MAKE_COMMAND_ONLY_STDERR = "make 2>&1 >/dev/null";
const std::string CppCompiler::CompileRunner::MAKE_COMMAND_STDOUT_AND_STDERR = "make 2>&1";


