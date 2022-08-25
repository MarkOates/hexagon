#pragma once


#include <string>


namespace Hexagon
{
   namespace Testing
   {
      class ClangBuildOutputResult
      {
      private:
         std::string message;
         std::string body;
         std::string filename;
         std::string type;
         int line_num;
         int column_num;
         std::string actual_error_message;
         int on_test_dump_line_num;
         int test_dump_line_num;

      public:
         ClangBuildOutputResult(std::string message="[unset-message]", std::string body="[unset-body]", std::string filename="[unset-filename]", std::string type="unknown", int line_num=-1, int column_num=-1, std::string actual_error_message="unknown", int on_test_dump_line_num=-1, int test_dump_line_num=-1);
         ~ClangBuildOutputResult();

         void set_message(std::string message);
         void set_body(std::string body);
         void set_filename(std::string filename);
         void set_type(std::string type);
         void set_line_num(int line_num);
         void set_column_num(int column_num);
         void set_actual_error_message(std::string actual_error_message);
         void set_on_test_dump_line_num(int on_test_dump_line_num);
         void set_test_dump_line_num(int test_dump_line_num);
         std::string get_message() const;
         std::string get_body() const;
         std::string get_filename() const;
         std::string get_type() const;
         int get_line_num() const;
         int get_column_num() const;
         std::string get_actual_error_message() const;
         int get_on_test_dump_line_num() const;
         int get_test_dump_line_num() const;
      };
   }
}



