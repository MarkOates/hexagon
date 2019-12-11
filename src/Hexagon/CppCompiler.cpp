

#include <Hexagon/CppCompiler.hpp>


#include <Blast/ShellCommandExecutor.hpp>
#include <iostream>
#include <sstream>


namespace CppCompiler
{
   CompileRunner::CompileRunner(std::string filename)
      : filename(filename)
   {}


   CompileRunner::~CompileRunner()
   {}


   std::string CompileRunner::run()
   {
      std::stringstream make_command_string;
      make_command_string << "make 2>&1"; // should be "make" by default
      Blast::ShellCommandExecutor shell_command_executor(make_command_string.str());
      std::string output = shell_command_executor.execute();
      std::cout << output << std::endl;
      return output;
   }
}


