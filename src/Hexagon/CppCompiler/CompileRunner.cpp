

#include <Hexagon/CppCompiler/CompileRunner.hpp>


#include <Blast/ShellCommandExecutor.hpp>
#include <iostream>
#include <sstream>


namespace CppCompiler
{
   CompileRunner::CompileRunner(std::string project_root_directory, std::string filename)
      : project_root_directory(project_root_directory)
      , filename(filename)
      , command_string(MAKE_COMMAND_ONLY_STDERR)
   {}


   CompileRunner::~CompileRunner()
   {}


   std::string CompileRunner::run()
   {
      std::string cmd
        = std::string("(")
        + "cd "
        + project_root_directory
        + " && "
        + command_string
        + ")"
        + "; echo FINAL_EXIT_CODE:$?";
      Blast::ShellCommandExecutor shell_command_executor(cmd);
      std::string output = shell_command_executor.execute();

      return output;
   }
}


const std::string CppCompiler::CompileRunner::MAKE_COMMAND_ONLY_STDOUT = "make";
const std::string CppCompiler::CompileRunner::MAKE_COMMAND_ONLY_STDERR = "make 2>&1 >/dev/null";
const std::string CppCompiler::CompileRunner::MAKE_COMMAND_STDOUT_AND_STDERR = "make 2>&1";


