#pragma once


#include <string>


class RailsMinitestTestRunner
{
private:
   std::string test_filename;

public:
   RailsMinitestTestRunner(std::string test_filename="undefined_test_file.rb");
   ~RailsMinitestTestRunner();

   static void command_line_exec_callback(std::string new_content);
   std::string get_execution_command();
   std::string run();
};

