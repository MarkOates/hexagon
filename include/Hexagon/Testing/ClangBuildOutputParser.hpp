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
         std::vector<std::string> lines;
         bool lines_parsed;
         std::string warnings_errors_generated_line;
         bool warnings_errors_generated_line_parsed;
         std::string WARNINGS_ERRORS_MATCHER;

      public:
         ClangBuildOutputParser(std::string clang_build_run_output="[unset-clang_build_run_output]");
         ~ClangBuildOutputParser();

         std::vector<Hexagon::Testing::ClangBuildOutputResult> get_clang_build_results() const;
         std::vector<std::string> get_error_messages_during_parsing() const;
         std::string get_warnings_errors_generated_line() const;
         std::string get_WARNINGS_ERRORS_MATCHER() const;
         void parse();
         std::vector<std::string> discard_irrelevant_lines();
         void parse_split_lines();
         void parse_warnings_errors_generated_line();
      };
   }
}



