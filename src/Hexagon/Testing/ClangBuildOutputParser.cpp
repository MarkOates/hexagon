

#include <Hexagon/Testing/ClangBuildOutputParser.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/RegexMatcher.hpp>
#include <iostream>


namespace Hexagon
{
namespace Testing
{


std::string ClangBuildOutputParser::NUM_WARNINGS_ERRORS_GENERATED_REGEX = "[0-9]+ (?:warning[s]?|error[s]?) generated\\.";


std::string ClangBuildOutputParser::WARNING_OR_ERROR_REGEX = "[TODO]";


ClangBuildOutputParser::ClangBuildOutputParser(std::string clang_build_run_output)
   : clang_build_run_output(clang_build_run_output)
   , warnings_errors_and_notes({})
   , warnings_errors_and_notes_parsed(false)
   , error_messages_during_parsing({})
   , lines({})
   , lines_parsed(false)
   , num_warnings_errors_generated_line("")
   , num_warnings_errors_generated_line_parsed(false)
   , parsed(false)
{
}


ClangBuildOutputParser::~ClangBuildOutputParser()
{
}


std::vector<Hexagon::Testing::ClangBuildOutputResult> ClangBuildOutputParser::get_warnings_errors_and_notes() const
{
   return warnings_errors_and_notes;
}


std::vector<std::string> ClangBuildOutputParser::get_error_messages_during_parsing() const
{
   return error_messages_during_parsing;
}


std::string ClangBuildOutputParser::get_num_warnings_errors_generated_line() const
{
   return num_warnings_errors_generated_line;
}


std::string ClangBuildOutputParser::get_NUM_WARNINGS_ERRORS_GENERATED_REGEX()
{
   return NUM_WARNINGS_ERRORS_GENERATED_REGEX;
}


std::string ClangBuildOutputParser::get_WARNING_OR_ERROR_REGEX()
{
   return WARNING_OR_ERROR_REGEX;
}


bool ClangBuildOutputParser::get_parsed() const
{
   return parsed;
}


void ClangBuildOutputParser::parse()
{
   if (parsed) return;
   parse_split_lines();
   parse_num_warnings_errors_generated_line();
   parse_warnings_errors_and_notes();
   parsed = true;
   return;
}

std::vector<std::string> ClangBuildOutputParser::discard_irrelevant_lines()
{
   // TODO in FUTURE
   return {};
}

void ClangBuildOutputParser::parse_split_lines()
{
   if (lines_parsed) return;
   Blast::StringSplitter splitter(clang_build_run_output, '\n');
   lines = splitter.split();
   return;
}

void ClangBuildOutputParser::parse_warnings_errors_and_notes()
{
   if (warnings_errors_and_notes_parsed) return;
   warnings_errors_and_notes_parsed = true;

   // TODO
   bool body_accumulation_started = false;
   Hexagon::Testing::ClangBuildOutputResult accumulated_parsed_output_result;

   for (int line_i=0; line_i<lines.size(); line_i++)
   {
      std::string &this_line = lines[line_i];
      std::string regex = "([a-zA-Z0-9/_\\.]+):([0-9]+):([0-9]+): (error|note|warning): (.+)";
      //https://cplusplus.com/reference/regex/ECMAScript/
      //https://regex101.com/r/cX0eP2/164


      RegexMatcher matcher(this_line, regex);
      std::vector<std::pair<int, int>> match_info = matcher.get_match_info();
      if (!match_info.empty())
      {
         if (match_info.size() != 1)
         {
            std::cout << "Weird error - expecting just 1 match in a line but there were several." << std::endl;
         }
         //else if (match_found)
         //{
            //std::cout << "Weird error - found another match but one has already been found." << std::endl;
         //}
         else
         {
            Hexagon::Testing::ClangBuildOutputResult parsed_output_result =
               Hexagon::Testing::ClangBuildOutputResult::build_from_message_line(this_line);
            parsed_output_result.set_body("");
            //parsed_output_result.set_parsed_from_test_dump_line_num(line_i);
            //parsed_output_result.set_body(this_line);

            if (parsed_output_result.get_type() != "note")
            {
               warnings_errors_and_notes.push_back(parsed_output_result);
               parsed_output_result.set_parsed_from_test_dump_line_num(line_i);
               parsed_output_result.set_body(this_line);
            }
            else
            {
               std::string new_body = warnings_errors_and_notes.back().get_body() + "\n" + this_line;
               warnings_errors_and_notes.back().set_body(new_body);
            }

            body_accumulation_started = true;
         }
         //std::cout << "# " << this_line << std::endl;
      }
      else
      {
         if (body_accumulation_started)
         {
            std::string new_body = warnings_errors_and_notes.back().get_body() + "\n" + this_line;
            warnings_errors_and_notes.back().set_body(new_body);
         }
         //std::cout << ". " << this_line << std::endl;
      }
   }

   return;
}

void ClangBuildOutputParser::parse_num_warnings_errors_generated_line()
{
   if (num_warnings_errors_generated_line_parsed) return;
   num_warnings_errors_generated_line_parsed = true;

   bool match_found = false;
   for (int line_i=0; line_i<lines.size(); line_i++)
   {
      std::string &this_line = lines[line_i];
      RegexMatcher matcher(this_line, NUM_WARNINGS_ERRORS_GENERATED_REGEX);
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
            num_warnings_errors_generated_line = this_line;
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


