

#include <Blast/Daemus/Daemus.hpp>
#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>
#include <vector>
#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>
#include <Blast/DirectoryExistenceChecker.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <sstream>
#include <iostream>
#include <iostream>
#include <unistd.h>
#include <Blast/ShellCommandExecutorWithCallback.hpp>


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

std::vector<Hexagon::Testing::GoogleTestRunTestResult> Daemus::run_component_test(Blast::Project::Component component)
{
   std::string name = component.get_name();
   std::string project_directory = component.get_project_root();
   std::string test_binary = component.generate_full_path_test_binary_filename();

   if (!Blast::DirectoryExistenceChecker(project_directory).exists())
   {
      std::stringstream error_message;
      error_message << "Daemus::run_component_test: error: "
                    << "the expected project directory \"" << project_directory << "\" "
                    << "does not exist";
      throw std::runtime_error(error_message.str());
   }
   if (!Blast::FileExistenceChecker(test_binary).exists())
   {
      std::stringstream error_message;
      error_message << "Daemus::run_component_test: error: "
                    << "the test binary \"" << test_binary << "\" "
                    << "does not exist";
      throw std::runtime_error(error_message.str());
   }

   // execute the test
   std::stringstream command;
   command << "("
              << "cd " << project_directory
              << " && "
              << test_binary
           << ")";
   std::string test_run_output = execute_command(command.str(), false);

   // parse the results
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(test_run_output);

   bool successful_parse = google_test_run_output_parser.parse();
   if (!successful_parse) throw std::runtime_error("fooobbarrr");
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> test_results =
      google_test_run_output_parser.get_parsed_test_results();

   return test_results;
}

void Daemus::run_build_quintessence_file(std::string project_directory, std::string quintessence_filename)
{
   if (!Blast::DirectoryExistenceChecker(project_directory).exists())
   {
      std::stringstream error_message;
      error_message << "Daemus::run_build_quintessence_file: error: "
                    << "the expected project directory \"" << project_directory << "\" "
                    << "does not exist";
      throw std::runtime_error(error_message.str());
   }
   if (!Blast::FileExistenceChecker(quintessence_build_executable).exists())
   {
      std::stringstream error_message;
      error_message << "Daemus::run_build_quintessence_file: error: "
                    << "the expected executable \"" << quintessence_build_executable << "\" "
                    << "is not present";
      throw std::runtime_error(error_message.str());
   }
   std::string full_path_to_quintessence_file = project_directory + "/" + quintessence_filename;
   if (!Blast::FileExistenceChecker(full_path_to_quintessence_file).exists())
   {
      std::stringstream error_message;
      error_message << "Daemus::run_build_quintessence_file: error: "
                    << "the quintessence file \"" << quintessence_filename << "\" "
                    << "does not exist";
      throw std::runtime_error(error_message.str());
   }

   std::stringstream command;
   command << "("
              << "cd " << project_directory
              << " && "
              << quintessence_build_executable << " -f " << quintessence_filename
           << ")";
   execute_command(command.str(), false);

   return;
}

void Daemus::output_pid()
{
   std::cout << "pid: " << getpid() << std::endl;
   return;
}

std::string Daemus::execute_command(std::string command, bool output_to_stdout)
{
   Blast::ShellCommandExecutorWithCallback shell_command_executor(
      command,
      output_to_stdout ? Blast::ShellCommandExecutorWithCallback::simple_cout_callback
                       : Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
   return shell_command_executor.execute();
}
} // namespace Daemus
} // namespace Blast


