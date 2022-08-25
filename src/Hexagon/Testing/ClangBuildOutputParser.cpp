

#include <Hexagon/Testing/ClangBuildOutputParser.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/RegexMatcher.hpp>


namespace Hexagon
{
namespace Testing
{


ClangBuildOutputParser::ClangBuildOutputParser(std::string clang_build_run_output)
   : clang_build_run_output(clang_build_run_output)
   , clang_build_results({})
   , error_messages_during_parsing({})
   , errors_warnings_generated_line("")
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


void ClangBuildOutputParser::parse()
{
   // split lines
   Blast::StringSplitter splitter(clang_build_run_output, '\n');
   std::vector<std::string> lines = splitter.split();

   // discard or filter out lines
   // snag known lines
   return;
}

std::vector<std::string> ClangBuildOutputParser::discard_irrelevant_lines()
{
   return {};
}

std::string ClangBuildOutputParser::extract_num_warnings_errors_generated_line()
{
   // TODO
   std::string basic_warnings_errors_matcher = R"REGEX([0-9]+ (?:warning[s]?|error[s]?) generated\\.)REGEX";
   RegexMatcher matcher(clang_build_run_output, basic_warnings_errors_matcher);
   return "";
}

int ClangBuildOutputParser::extract_num_errors_generated()
{
   return 0;
}

int ClangBuildOutputParser::extract_num_warnings_generated()
{
   return 0;
}
} // namespace Testing
} // namespace Hexagon


