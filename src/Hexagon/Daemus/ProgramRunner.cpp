

#include <Hexagon/Daemus/ProgramRunner.hpp>
#include <sstream>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/System/Config.hpp>
#include <iostream>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/System/Config.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
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
#include <filesystem>
#include <chrono>


namespace Hexagon
{
namespace Daemus
{


ProgramRunner::ProgramRunner(std::string quintessence_build_executable)
   : quintessence_build_executable(quintessence_build_executable)
   , daemus_build_file_directory("/Users/markoates/Repos/hexagon/bin/programs/data/tmp")
   , daemus_build_filename("daemus_build.txt")
{
}


ProgramRunner::~ProgramRunner()
{
}


std::string ProgramRunner::get_daemus_build_file_directory()
{
   return daemus_build_file_directory;
}


std::string ProgramRunner::get_daemus_build_filename()
{
   return daemus_build_filename;
}


void ProgramRunner::run()
{
   al_init();
   Hexagon::System::Config hexagon_config;
   hexagon_config.initialize();

   std::string project_directory = hexagon_config.get_default_navigator_directory();

   cd_to_project_directory_and_run_with_rerun(project_directory);
   //watch_for_buildfile(project_directory);
   return;
}

void ProgramRunner::process_oldest_file_in_builds_folder()
{
   // TODO fill out this function
   std::string oldest_filename = "foobar.txt";
   std::string current_location = "location/foobar.txt";
   std::string new_location = "new_location/foobar.txt";

   //if (!file_exist)
   {      
      //throw
   }


   //try
   //{
      //std::filesystem::rename("from.txt", "to.txt");
      //system("dir /od /b");
   //}
   //catch (std::filesystem::filesystem_error& e)
   //{
   //   std::cout << e.what() << '\n';
   //}
   return;
}

void ProgramRunner::run_full_rebuild()
{
   std::string full_rebuild_command = "make clean && make programs && make && make clean && make programs && make";
   execute_command(full_rebuild_command);
}

void ProgramRunner::run_in_holding_pattern()
{
   al_init();
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   // have event source initialized here

   al_destroy_event_queue(event_queue);
   return;
}

void ProgramRunner::run_simple_echo_command()
{
   execute_command("printf \"hello\"");
}

void ProgramRunner::run_simple_sleep_command()
{
   execute_command("echo \"sleeping\"; sleep 0.5; echo \"done\"");
}

void ProgramRunner::run_once(std::string project_directory)
{
   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::stringstream result_command;
   result_command << "cd "
                  << project_directory
                  << " && "
                  << actual_command_to_execute_in_project_directory;

   std::string output = execute_command(result_command.str());
}

void ProgramRunner::cd_to_project_directory_and_run_with_rerun(std::string project_directory)
{
   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::string build_command = "rerun" \
      " " \
      "-c" \
      " " \
      "--background" \
      " " \
      "--ignore \"{**/bin/programs/data/tmp/*,**/documentation/*\"}" \
      " " \
      "-p \"**/*.{rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}\"" \
      " " \
      "\"(cd ";

   build_command += project_directory + " && " + actual_command_to_execute_in_project_directory + ")\"";

   std::string build_command_wrapped = "(cd " + project_directory + " && " + build_command + ")";

   std::string output = execute_command(build_command);
   return;
}

void ProgramRunner::watch_for_buildfile(std::string project_directory)
{
   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::cout << "watching for buildfile (\"" << get_daemus_build_filename() << "\")" << std::endl;
   std::cout << "... in directory (\"" << get_daemus_build_file_directory() << "\")" << std::endl;

   std::string build_command = "rerun" \
     " " \
     "-c" \
     " " \
     "--background" \
     " " \
     "--dir \"" + get_daemus_build_file_directory() + "\"" \
     " " \
     "-p \"" + get_daemus_build_filename() + "\"" \
     " " \
     "\"(cd ";

   build_command += project_directory + " && " + actual_command_to_execute_in_project_directory + ")\"";
   std::string output = execute_command(build_command);
   return;
}

void ProgramRunner::run_with_rerun(std::string project_directory)
{
   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::string build_command = "rerun" \
     " " \
     "-c" \
     " " \
     "--background" \
     " " \
     "--ignore \"**/bin/programs/data/tmp/*\"" \
     " " \
     "-p \"**/*.{rb,js,tsx,coffee,css,scss,sass,erb,html,haml,ru,yml,slim,md,feature,c,h,cpp,hpp,txt,cfg}\"" \
     " " \
     "\"(cd ";

   build_command += project_directory + " && " + actual_command_to_execute_in_project_directory + ")\"";
   std::string output = execute_command(build_command);
   return;
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

std::vector<Hexagon::Testing::GoogleTestRunTestResult> ProgramRunner::run_component_test(Blast::Project::Component component)
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
   std::string test_run_output = __execute_command(command.str(), false);

   // parse the results
   Hexagon::Testing::GoogleTestRunOutputParser google_test_run_output_parser(test_run_output);

   bool successful_parse = google_test_run_output_parser.parse();
   if (!successful_parse) throw std::runtime_error("fooobbarrr");
   std::vector<Hexagon::Testing::GoogleTestRunTestResult> test_results =
      google_test_run_output_parser.get_parsed_test_results();

   return test_results;
}

void ProgramRunner::run_build_quintessence_file(std::string project_directory, std::string quintessence_filename)
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
   __execute_command(command.str(), false);

   return;
}

void ProgramRunner::output_pid()
{
   std::cout << "pid: " << getpid() << std::endl;
   return;
}

std::string ProgramRunner::__execute_command(std::string command, bool output_to_stdout)
{
   Blast::ShellCommandExecutorWithCallback shell_command_executor(
      command,
      output_to_stdout ? Blast::ShellCommandExecutorWithCallback::simple_cout_callback
                       : Blast::ShellCommandExecutorWithCallback::simple_silent_callback
   );
   return shell_command_executor.execute();
}

std::string ProgramRunner::find_oldest_filename(std::string path)
{
   // TODO check that path exists
   // TODO check that path is not empty, or return ""

   std::vector<std::pair<std::filesystem::file_time_type, std::string>> listing;
   for (const auto &entry : std::filesystem::directory_iterator(path))
   {
      std::filesystem::file_time_type file_time = std::filesystem::last_write_time(entry);
      std::string filename = entry.path().string();
      listing.push_back(std::pair<std::filesystem::file_time_type, std::string>(file_time, filename));
   }

   //std::random_device rd;
   //std::mt19937 g(rd());
   //std::shuffle(v.begin(), v.end(), g);

   // TODO: confirm this sort is actually doing what is expected
   std::sort(listing.begin(), listing.end());

   return listing[0].second;
}
} // namespace Daemus
} // namespace Hexagon


