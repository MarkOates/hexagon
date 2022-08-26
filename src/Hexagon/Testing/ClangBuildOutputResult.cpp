

#include <Hexagon/Testing/ClangBuildOutputResult.hpp>
#include <sstream>
#include <Blast/StringSplitter.hpp>
#include <Blast/String/Trimmer.hpp>
#include <cstdlib>


namespace Hexagon
{
namespace Testing
{


ClangBuildOutputResult::ClangBuildOutputResult(std::string message_line, std::string body, std::string filename, std::string type, int line_num, int column_num, std::string message, int on_test_dump_line_num, int test_dump_line_num)
   : message_line(message_line)
   , body(body)
   , filename(filename)
   , type(type)
   , line_num(line_num)
   , column_num(column_num)
   , message(message)
   , on_test_dump_line_num(on_test_dump_line_num)
   , test_dump_line_num(test_dump_line_num)
{
}


ClangBuildOutputResult::~ClangBuildOutputResult()
{
}


void ClangBuildOutputResult::set_message_line(std::string message_line)
{
   this->message_line = message_line;
}


void ClangBuildOutputResult::set_body(std::string body)
{
   this->body = body;
}


void ClangBuildOutputResult::set_filename(std::string filename)
{
   this->filename = filename;
}


void ClangBuildOutputResult::set_type(std::string type)
{
   this->type = type;
}


void ClangBuildOutputResult::set_line_num(int line_num)
{
   this->line_num = line_num;
}


void ClangBuildOutputResult::set_column_num(int column_num)
{
   this->column_num = column_num;
}


void ClangBuildOutputResult::set_message(std::string message)
{
   this->message = message;
}


void ClangBuildOutputResult::set_on_test_dump_line_num(int on_test_dump_line_num)
{
   this->on_test_dump_line_num = on_test_dump_line_num;
}


void ClangBuildOutputResult::set_test_dump_line_num(int test_dump_line_num)
{
   this->test_dump_line_num = test_dump_line_num;
}


std::string ClangBuildOutputResult::get_message_line() const
{
   return message_line;
}


std::string ClangBuildOutputResult::get_body() const
{
   return body;
}


std::string ClangBuildOutputResult::get_filename() const
{
   return filename;
}


std::string ClangBuildOutputResult::get_type() const
{
   return type;
}


int ClangBuildOutputResult::get_line_num() const
{
   return line_num;
}


int ClangBuildOutputResult::get_column_num() const
{
   return column_num;
}


std::string ClangBuildOutputResult::get_message() const
{
   return message;
}


int ClangBuildOutputResult::get_on_test_dump_line_num() const
{
   return on_test_dump_line_num;
}


int ClangBuildOutputResult::get_test_dump_line_num() const
{
   return test_dump_line_num;
}


Hexagon::Testing::ClangBuildOutputResult ClangBuildOutputResult::build_from_message_line(std::string line)
{
   Hexagon::Testing::ClangBuildOutputResult result;
   result.message_line = line;

   // TODO: validate line is valid
   Blast::StringSplitter splitter(line, ':');
   std::vector<std::string> tokens = splitter.split();

   if (tokens.size() < 4)
   {
      std::stringstream error_message;
      error_message << "Hexagon::Testing::ClangBuildOutputResult error: "
                    << "Expecting more than 4 tokens (elements separated by ':' character).";
      throw std::runtime_error(error_message.str());
   }
   else
   {
      result.filename = tokens[0];
      result.line_num = atoi(tokens[1].c_str());
      result.column_num = atoi(tokens[2].c_str());
      result.type = Blast::String::Trimmer(tokens[3]).trim();
      size_t message_start_pos = tokens[0].size() + 1
                               + tokens[1].size() + 1
                               + tokens[2].size() + 1
                               + tokens[3].size() + 2;
      result.message = line.substr(message_start_pos);
   }

   return result;
}
} // namespace Testing
} // namespace Hexagon


