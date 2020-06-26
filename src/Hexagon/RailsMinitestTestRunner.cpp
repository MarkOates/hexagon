

#include <Hexagon/RailsMinitestTestRunner.hpp>


#include <Blast/ShellCommandExecutor.hpp>
#include <iostream>
#include <sstream>


RailsMinitestTestRunner::RailsMinitestTestRunner(std::string test_filename)
   : test_filename(test_filename)
{}


RailsMinitestTestRunner::~RailsMinitestTestRunner() {}


void RailsMinitestTestRunner::command_line_exec_callback(std::string new_content)
{
   std::cout << "####>" << new_content << "<####" << std::endl;
}


std::string RailsMinitestTestRunner::get_execution_command()
{
   std::stringstream test_command_string;
   test_command_string << "bin/rails test " << test_filename << " -v";
   return test_command_string.str();
}


std::string RailsMinitestTestRunner::run()
{
   Blast::ShellCommandExecutor shell_command_executor(get_execution_command());
   std::string output = shell_command_executor.execute(RailsMinitestTestRunner::command_line_exec_callback);
   return output;
}


