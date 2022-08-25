

#include <Hexagon/Testing/ClangBuildOutputResult.hpp>



namespace Hexagon
{
namespace Testing
{


ClangBuildOutputResult::ClangBuildOutputResult(std::string message, std::string body, std::string filename, std::string type, int line_num, int column_num, std::string actual_error_message, int on_test_dump_line_num, int test_dump_line_num)
   : message(message)
   , body(body)
   , filename(filename)
   , type(type)
   , line_num(line_num)
   , column_num(column_num)
   , actual_error_message(actual_error_message)
   , on_test_dump_line_num(on_test_dump_line_num)
   , test_dump_line_num(test_dump_line_num)
{
}


ClangBuildOutputResult::~ClangBuildOutputResult()
{
}


void ClangBuildOutputResult::set_message(std::string message)
{
   this->message = message;
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


void ClangBuildOutputResult::set_actual_error_message(std::string actual_error_message)
{
   this->actual_error_message = actual_error_message;
}


void ClangBuildOutputResult::set_on_test_dump_line_num(int on_test_dump_line_num)
{
   this->on_test_dump_line_num = on_test_dump_line_num;
}


void ClangBuildOutputResult::set_test_dump_line_num(int test_dump_line_num)
{
   this->test_dump_line_num = test_dump_line_num;
}


std::string ClangBuildOutputResult::get_message() const
{
   return message;
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


std::string ClangBuildOutputResult::get_actual_error_message() const
{
   return actual_error_message;
}


int ClangBuildOutputResult::get_on_test_dump_line_num() const
{
   return on_test_dump_line_num;
}


int ClangBuildOutputResult::get_test_dump_line_num() const
{
   return test_dump_line_num;
}


} // namespace Testing
} // namespace Hexagon


