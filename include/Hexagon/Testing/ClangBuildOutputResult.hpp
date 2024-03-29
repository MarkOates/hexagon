#pragma once


#include <Hexagon/Testing/ClangBuildOutputResult.hpp>
#include <string>


namespace Hexagon
{
   namespace Testing
   {
      class ClangBuildOutputResult
      {
      private:
         std::string message_line;
         std::string body;
         std::string filename;
         std::string type;
         int line_num;
         int column_num;
         std::string message;
         int parsed_from_test_dump_line_num;

      protected:


      public:
         ClangBuildOutputResult(std::string message_line="[unset-message]", std::string body="[unset-body]", std::string filename="[unset-filename]", std::string type="unknown", int line_num=-1, int column_num=-1, std::string message="unknown", int parsed_from_test_dump_line_num=-1);
         ~ClangBuildOutputResult();

         void set_message_line(std::string message_line);
         void set_body(std::string body);
         void set_filename(std::string filename);
         void set_type(std::string type);
         void set_line_num(int line_num);
         void set_column_num(int column_num);
         void set_message(std::string message);
         void set_parsed_from_test_dump_line_num(int parsed_from_test_dump_line_num);
         std::string get_message_line() const;
         std::string get_body() const;
         std::string get_filename() const;
         std::string get_type() const;
         int get_line_num() const;
         int get_column_num() const;
         std::string get_message() const;
         int get_parsed_from_test_dump_line_num() const;
         static Hexagon::Testing::ClangBuildOutputResult build_from_message_line(std::string line="[unset-line]");
      };
   }
}



