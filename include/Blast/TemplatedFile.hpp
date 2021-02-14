#pragma once


#include <string>
#include <vector>


namespace Blast
{
   class TemplatedFile
   {
   private:
      std::string template_content;
      std::vector<std::pair<std::string, std::string>> insertion_variables;

   public:
      TemplatedFile(std::string template_content="[[GREETING]], [[SUBJECT]]!", std::vector<std::pair<std::string, std::string>> insertion_variables={ { "[[GREETING]]", "Hello" }, { "[[SUBJECT]]", "World" } });
      ~TemplatedFile();

      void set_insertion_variables(std::vector<std::pair<std::string, std::string>> insertion_variables);
      std::vector<std::pair<std::string, std::string>> get_insertion_variables();
      std::string __replace(std::string str="source string", std::string from="source", std::string to="result");
      std::string generate_content();
   };
}



