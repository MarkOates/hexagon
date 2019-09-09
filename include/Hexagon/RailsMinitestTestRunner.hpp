
#pragma once

class RailsMinitestTestRunner
{
private:
   std::string test_filename;

public:
   RailsMinitestTestRunner(std::string test_filename)
      : test_filename(test_filename)
   {}
   ~RailsMinitestTestRunner() {}

   std::string get_execution_command()
   {
      std::stringstream test_command_string;
      test_command_string << "bin/rails test " << test_filename << " -v";
      return test_command_string.str();
   }

   std::string run()
   {
      Blast::ShellCommandExecutor shell_command_executor(get_execution_command());
      std::string output = shell_command_executor.execute(command_line_exec_callback);
      return output;
   }
};

