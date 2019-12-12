#pragma once


#include <string>


namespace CppCompiler
{
   class CompileRunner
   {
   private:
      static const std::string MAKE_COMMAND_ONLY_STDERR;
      static const std::string MAKE_COMMAND_ONLY_STDOUT;
      static const std::string MAKE_COMMAND_STDOUT_AND_STDERR;
      std::string project_root_directory;
      std::string filename;
      std::string command_string;

   public:
      CompileRunner(std::string project_root_directory, std::string filename);
      ~CompileRunner();

      std::string run();
   };
};


