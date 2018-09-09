

#include <Blast/ShellCommandExecutor.hpp>

#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>


namespace Blast
{


ShellCommandExecutor::ShellCommandExecutor(std::string command)
   : command(command)
{
}


ShellCommandExecutor::~ShellCommandExecutor()
{
}


std::string ShellCommandExecutor::execute()
{
   static const int BUFFER_SIZE = 128;

   std::array<char, BUFFER_SIZE> buffer;
   std::string result;
   std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

   if (!pipe) throw std::runtime_error("ShellCommandExecutor::execute(): Error: popen() failed.");

   while (!feof(pipe.get()))
      if (fgets(buffer.data(), BUFFER_SIZE, pipe.get()) != nullptr)
         result += buffer.data();

   return result;
}


} // namespace Blast


