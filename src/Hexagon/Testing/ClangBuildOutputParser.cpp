

#include <Hexagon/Testing/ClangBuildOutputParser.hpp>
#include <Blast/StringSplitter.hpp>


namespace Hexagon
{
namespace Testing
{


ClangBuildOutputParser::ClangBuildOutputParser(std::string clang_build_run_output)
   : clang_build_run_output(clang_build_run_output)
   , clang_build_results({})
   , error_messages_during_parsing({})
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
} // namespace Testing
} // namespace Hexagon


