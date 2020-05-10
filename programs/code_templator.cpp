#include <allegro5/allegro.h>


#include <Blast/TemplatedFile.hpp>


std::string guard_throw_with_error_message(std::string condition, std::string class_name, std::string function_name, std::string message)
{
   std::string template_content = R"END(if ({{CONDITION}})
{
   std::string_stream error_message;
   error_message << "{{CLASS_NAME}}" << "::" << "{{FUNCTION_NAME}}" << ": error: " << "{{MESSAGE}}";
   throw std::runtime_error(error_message.str());
})END";

   std::vector<std::pair<std::string, std::string>> insertion_variables = {
      { "{{CONDITION}}", condition },
      { "{{CLASS_NAME}}", class_name },
      { "{{FUNCTION_NAME}}", function_name },
      { "{{MESSAGE}}", message },
   };

   Blast::TemplatedFile templated_file(template_content, insertion_variables);

   return templated_file.generate_content();
}



std::string divider()
{
   return "==========================================================";
}



#include <iostream>

int main(int argc, char **argv)
{
   std::string class_name = argv[1];

   std::cout << divider() << std::endl;
   std::cout << guard_throw_with_error_message("!argument", "Foobar::ClassName", "doing_the_thing", "argument cannot be a nullptr") << std::endl;
   std::cout << divider() << std::endl;

   return 0;
}
