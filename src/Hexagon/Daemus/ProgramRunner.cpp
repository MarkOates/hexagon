

#include <Hexagon/Daemus/ProgramRunner.hpp>

#include <Blast/DirectoryExistenceChecker.hpp>
#include <Blast/FileExistenceChecker.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <Hexagon/System/Config.hpp>
#include <Hexagon/Testing/GoogleTestRunOutputParser.hpp>
#include <Hexagon/Testing/GoogleTestRunTestResult.hpp>
#include <chrono>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <vector>


namespace Hexagon
{
namespace Daemus
{


ProgramRunner::ProgramRunner(std::string quintessence_build_executable)
   : quintessence_build_executable(quintessence_build_executable)
   , daemus_buildfile_directory("/Users/markoates/Repos/hexagon/bin/programs/data/tmp/")
   , daemus_buildfile_filename("daemus_build.txt")
{
}


ProgramRunner::~ProgramRunner()
{
}


std::string ProgramRunner::get_daemus_buildfile_directory() const
{
   return daemus_buildfile_directory;
}


std::string ProgramRunner::get_daemus_buildfile_filename() const
{
   return daemus_buildfile_filename;
}


void ProgramRunner::run(bool watch_for_changes_in_tree_and_not_buildfile)
{
   al_init();

   if (watch_for_changes_in_tree_and_not_buildfile)
   {
      Hexagon::System::Config hexagon_config;
      hexagon_config.initialize();
      std::string project_directory = hexagon_config.get_default_navigator_directory();
      cd_to_project_directory_and_run_with_rerun(project_directory);
   }
   else
   {
      Hexagon::System::Config hexagon_config;
      hexagon_config.initialize();
      std::string project_directory = hexagon_config.get_default_navigator_directory();
      watch_for_buildfile(project_directory);
   }

   al_uninstall_system();
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
   al_uninstall_system();
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

   // TODO: note this override of 
   project_directory = "`cat /Users/markoates/Repos/hexagon/bin/programs/data/tmp/current_project_directory.txt`";
   //project_directory = "/Users/markoates/Repos/hexagon/ ";

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
      "--ignore \"{**/bin/programs/data/tmp/*,**bin/programs/data/builds/*,**/documentation/*\"}" \
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
   // this will, being run from any directory, will watch for a new buildfile in the "project_directory"
   // (as set by the hexagon config), and then cd into that directory and run make focus

   std::string actual_command_to_execute_in_project_directory = "make focus";

   std::cout << "watching for buildfile \"" << get_daemus_buildfile_filename() << "\" "
             << "in directory (\"" << get_daemus_buildfile_directory() << "\""
             << std::endl;

   std::string build_command = "rerun" \
     " " \
     "-c" \
     " " \
     "--background" \
     " " \
     "--dir \"" + get_daemus_buildfile_directory() + "\"" \
     " " \
     "-p \"" + get_daemus_buildfile_filename() + "\"" \
     " "
     //"\"(" \
     //"cd "
     ;

   //project_directory = "`cat /Users/markoates/Repos/hexagon/bin/programs/data/tmp/current_project_directory.txt` ";

   //build_command += project_directory + " && " + actual_command_to_execute_in_project_directory + ")\"";
   build_command += "\"(/Users/markoates/Repos/hexagon/bin/programs/daemus run_once)\"";

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
   //build_command += "(/Users/markoates/Repos/hexagon/bin/programs/daemus run_once)\"";

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
   shell_command_executor.set_capture_stderr(false); // TODO: Remove this line
                                                     // NOTE: This should probably be set to true. A recent
                                                     // change to Blast::ShellCommandExecutor resulted in
                                                     // stderr being captured by default, and as such this
                                                     // command is now running with errors.
   return shell_command_executor.execute();
}

std::string ProgramRunner::find_oldest_filename(std::string path, bool ignore_dotfiles)
{
   // check that path exists, or raise
   if (!Blast::DirectoryExistenceChecker(path).exists())
   {
      std::stringstream error_message;
      error_message << "[Hexagon::Daemus::ProgramRunner::find_oldest_filename] error: The directory "
                    << "\"" << path << "\" does not exist";
      throw std::runtime_error(error_message.str());
   }

   std::vector<std::pair<std::filesystem::file_time_type, std::string>> listing;
   for (const auto &entry : std::filesystem::directory_iterator(path))
   {
      std::filesystem::file_time_type file_time = std::filesystem::last_write_time(entry);
      std::string filename = entry.path().filename();
      std::string full_path_filename = entry.path().string();

      if (ignore_dotfiles)
      {
         bool file_is_a_dotfile = false;
         if (!filename.empty() && (filename[0] == '.')) file_is_a_dotfile = true;
         if (!file_is_a_dotfile)
         {
            listing.push_back(std::pair<std::filesystem::file_time_type, std::string>(file_time, full_path_filename));
         }
      }
      else
      {
         listing.push_back(std::pair<std::filesystem::file_time_type, std::string>(file_time, full_path_filename));
      }
   }

   if (listing.empty()) return "";

   std::sort(listing.begin(), listing.end());

   return listing[0].second;
}


} // namespace Daemus
} // namespace Hexagon


