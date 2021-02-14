

#include <Hexagon/PasteboardData.hpp>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <sstream>
#include <Blast/ShellCommandExecutorWithCallback.hpp>
#include <iostream>
#include <sstream>


namespace Hexagon
{


PasteboardData::PasteboardData()
{
}


PasteboardData::~PasteboardData()
{
}


bool PasteboardData::store(std::string content)
{
   std::stringstream command;

   content = __replace(content, "\\\\", "\\\\\\\\");

   content = __replace(content, "\"", "\\\"");

   //content = __replace(content, "\\\\", "\\\\\\\\");
   content = __replace(content, "\\", "\\\\");

   content = __replace(content, "\\a", "\\\\a");
   content = __replace(content, "\\b", "\\\\b");
   content = __replace(content, "\\c", "\\\\c");
   content = __replace(content, "\\f", "\\\\f");
   content = __replace(content, "\\n", "\\\\n");
   content = __replace(content, "\\r", "\\\\r");
   content = __replace(content, "\\t", "\\\\t");
   content = __replace(content, "\\v", "\\\\v");
   content = __replace(content, "\\'", "\\\\'");
   //content = __replace(content, "\\\\", "\\\\c");

   //content = __replace(content, "\\", "\\\\");
   content = __replace(content, "\"", "\\\"");
   content = __replace(content, "$", "\\$");
   content = __replace(content, "%", "%%");

   //content = __replace(content, "\\\"", "\\\"");

   command << "printf \"" << content << "\" | pbcopy" << std::endl;
   Blast::ShellCommandExecutorWithCallback executor(
         command.str(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
   executor.execute();
   return true;
}

std::string PasteboardData::retrieve()
{
   std::stringstream command;
   command << "pbpaste" << std::endl;
   Blast::ShellCommandExecutorWithCallback executor(
         command.str(),
         Blast::ShellCommandExecutorWithCallback::simple_silent_callback
      );
   std::string result = executor.execute();
   return result;
}

std::string PasteboardData::__replace(std::string str, std::string from, std::string to)
{
   size_t start_pos = 0;
   while((start_pos = str.find(from, start_pos)) != std::string::npos)
   {
     str.replace(start_pos, from.length(), to);
     start_pos += to.length();
   }
   return str;
}
} // namespace Hexagon


