

#include <Blast/ShellCommandExecutorWithCallback.hpp>

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>


namespace Blast
{


ShellCommandExecutorWithCallback::ShellCommandExecutorWithCallback(std::string command, std::function<void(std::string)> callback, bool capture_stderr)
   : command(command)
   , callback(callback)
   , capture_stderr(capture_stderr)
   , exit_status_DISABLED__not_supported_on_windows(0)
   , executed_successfully(false)
   , finished(false)
{
}


ShellCommandExecutorWithCallback::~ShellCommandExecutorWithCallback()
{
}


void ShellCommandExecutorWithCallback::set_capture_stderr(bool capture_stderr)
{
   this->capture_stderr = capture_stderr;
}


bool ShellCommandExecutorWithCallback::get_capture_stderr() const
{
   return capture_stderr;
}


uint32_t ShellCommandExecutorWithCallback::get_exit_status_DISABLED__not_supported_on_windows() const
{
   return exit_status_DISABLED__not_supported_on_windows;
}


bool ShellCommandExecutorWithCallback::get_executed_successfully() const
{
   return executed_successfully;
}


bool ShellCommandExecutorWithCallback::get_finished() const
{
   return finished;
}


void ShellCommandExecutorWithCallback::simple_silent_callback(std::string string_for_appending)
{
   return;
}

void ShellCommandExecutorWithCallback::simple_cout_callback(std::string string_for_appending)
{
   std::cout << string_for_appending;
}

std::string ShellCommandExecutorWithCallback::execute()
{
   finished = false;
   executed_successfully = false;
   //exit_status = 0; // TODO: NOTE: Disabled because the implementation does not work on Windows
                      // TODO: see other comments regarding coverage of this issue
   static const int BUFFER_SIZE = 128;
   // NOTE: this technique will stream cerr into cout, so if future implementations were to capture
   // cout and cerr into different result strings, this command would need to be modififed.
   std::string full_command = capture_stderr ? "(" + command + ") 2>&1" : command;

   std::array<char, BUFFER_SIZE> buffer;
   std::string result;
   //std::shared_ptr<FILE> pipe(popen(full_command.c_str(), "r"), pclose);
   FILE* pipe = popen(full_command.c_str(), "r");

   if (!pipe) throw std::runtime_error("ShellCommandExecutor::execute(): Error: popen() failed.");

   while (!feof(pipe))
      if (fgets(buffer.data(), BUFFER_SIZE, pipe) != nullptr)
      {
         result += buffer.data();
         callback(buffer.data());
      }

   int pclose_result = pclose(pipe);

   // TODO: Add an implementation that works on windows
   // NOTE: This is not supported on Windows, so is disabled
   //if(WIFEXITED(pclose_result)) {
       ////If you need to do something when the pipe exited, this is the time.
       //exit_status=WEXITSTATUS(pclose_result);
   //}

   executed_successfully = (pclose_result == 0);

   finished = true;

   return result;
}


} // namespace Blast


