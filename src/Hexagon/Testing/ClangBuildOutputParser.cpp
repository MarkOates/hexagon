

#include <Hexagon/Testing/ClangBuildOutputParser.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <iostream>


namespace Hexagon
{
namespace Testing
{


std::string ClangBuildOutputParser::WARNINGS_ERRORS_MATCHER = "[0-9]+ (?:warning[s]?|error[s]?) generated\\.";


ClangBuildOutputParser::ClangBuildOutputParser(std::string clang_build_run_output)
   : clang_build_run_output(clang_build_run_output)
   , clang_build_results({})
   , error_messages_during_parsing({})
   , lines({})
   , lines_parsed(false)
   , warnings_errors_generated_line("")
   , warnings_errors_generated_line_parsed(false)
{
}


ClangBuildOutputParser::~ClangBuildOutputParser()
{
}


std::vector<Hexagon::Testing::ClangBuildOutputResult> ClangBuildOutputParser::get_clang_build_results() const
{
   return clang_build_results;
}


std::vector<std::string> ClangBuildOutputParser::get_error_messages_during_parsing() const
{
   return error_messages_during_parsing;
}


std::string ClangBuildOutputParser::get_warnings_errors_generated_line() const
{
   return warnings_errors_generated_line;
}


std::string ClangBuildOutputParser::get_WARNINGS_ERRORS_MATCHER()
{
   return WARNINGS_ERRORS_MATCHER;
}


void ClangBuildOutputParser::parse()
{
   // split lines
   parse_split_lines();

   parse_warnings_errors_generated_line();

   // discard or filter out lines
   // snag known lines
   return;
}

std::vector<std::string> ClangBuildOutputParser::discard_irrelevant_lines()
{
   return {};
}

void ClangBuildOutputParser::parse_split_lines()
{
   if (lines_parsed) return;
   Blast::StringSplitter splitter(clang_build_run_output, '\n');
   lines = splitter.split();
   return;
}

void ClangBuildOutputParser::parse_warnings_errors_generated_line()
{
   if (warnings_errors_generated_line_parsed) return;
   warnings_errors_generated_line_parsed = true;

   bool match_found = false;
   for (int line_i=0; line_i<lines.size(); line_i++)
   {
      std::string &this_line = lines[line_i];
      RegexMatcher matcher(this_line, WARNINGS_ERRORS_MATCHER);
      std::vector<std::pair<int, int>> match_info = matcher.get_match_info();
      if (!match_info.empty())
      {
         if (match_info.size() != 1)
         {
            std::cout << "Weird error - expecting just 1 match in a line but there were several." << std::endl;
         }
         else if (match_found)
         {
            std::cout << "Weird error - found another match but one has already been found." << std::endl;
         }
         else
         {
            match_found = true;
            warnings_errors_generated_line = this_line;
         }
         //std::cout << "# " << this_line << std::endl;
      }
      else
      {
         //std::cout << ". " << this_line << std::endl;
      }
   }

   return;
}
} // namespace Testing
} // namespace Hexagon


