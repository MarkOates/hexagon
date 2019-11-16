#pragma once


#include <string>


namespace CppCompiler
{
   class CompileRunner
   {
   private:
      std::string filename;

   public:
      CompileRunner(std::string filename);
      ~CompileRunner();

      std::string run();
   };
};


