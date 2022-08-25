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
         std::vector<Hexagon::Testing::ClangBuildOutputResult> warnings_and_errors;
         bool warnings_and_errors_parsed;
         std::vector<std::string> error_messages_during_parsing;
         std::vector<std::string> lines;
         bool lines_parsed;
         std::string num_warnings_errors_generated_line;
         bool num_warnings_errors_generated_line_parsed;
         static std::string NUM_WARNINGS_ERRORS_GENERATED_REGEX;
         static std::string WARNING_OR_ERROR_REGEX;
         bool parsed;

      public:
         ClangBuildOutputParser(std::string clang_build_run_output="[unset-clang_build_run_output]");
         ~ClangBuildOutputParser();

         std::vector<Hexagon::Testing::ClangBuildOutputResult> get_warnings_and_errors() const;
         std::vector<std::string> get_error_messages_during_parsing() const;
         std::string get_num_warnings_errors_generated_line() const;
         static std::string get_NUM_WARNINGS_ERRORS_GENERATED_REGEX();
         static std::string get_WARNING_OR_ERROR_REGEX();
         bool get_parsed() const;
         void parse();
         std::vector<std::string> discard_irrelevant_lines();
         void parse_split_lines();
         void parse_warnings_and_errors();
         void parse_num_warnings_errors_generated_line();
      };
   }
}



