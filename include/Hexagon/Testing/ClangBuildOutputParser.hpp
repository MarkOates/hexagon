#pragma once


#include <Hexagon/Testing/ClangBuildOutputResult.hpp>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace Testing
   {
      class ClangBuildOutputParser
      {
      private:
         std::string clang_build_run_output;
         std::vector<Hexagon::Testing::ClangBuildOutputResult> clang_build_results;
         std::vector<std::string> error_messages_during_parsing;

      public:
         ClangBuildOutputParser(std::string clang_build_run_output="[unset-clang_build_run_output]");
         ~ClangBuildOutputParser();

         std::vector<Hexagon::Testing::ClangBuildOutputResult> get_clang_build_results() const;
         std::vector<std::string> get_error_messages_during_parsing() const;
         void parse();
      };
   }
}



