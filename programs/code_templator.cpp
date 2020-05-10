#include <allegro5/allegro.h>


#include <Blast/TemplatedFile.hpp>
#include <yaml-cpp/yaml.h>



#include <fstream>
bool file_put_contents(std::string filename, std::string contents)
{
   std::ofstream file;
   file.open(filename.c_str());
   if (!file.is_open()) return false;
   file << contents.c_str();
   file.close();
   return true;
}



class CodeTemplate
{
public:
   std::string name;
   std::string template_content;
   std::vector<std::string> variables;

   std::string fill(std::vector<std::pair<std::string, std::string>> insertion_variables)
   {
      Blast::TemplatedFile templated_file(template_content, insertion_variables);
      return templated_file.generate_content();
   }
};



#include <iostream>

namespace YAML {
   template<>
   struct convert<CodeTemplate> {
      static Node encode(const CodeTemplate& object) {
         Node node;
         node.push_back(object.name);
         node.push_back(object.template_content);
         for (auto &variable : object.variables)
         {
            node["variables"].push_back(variable);
         }
         return node;
      }

      static bool decode(const Node& node, CodeTemplate& object) {
         if(!node.IsMap()) { std::cout << "Error: Expecting node to be map"; }

         if (!node["name"]) { std::cout << "Error: Expecting \"name\" node"; }
         else { object.name = node["name"].as<std::string>(); }

         if (!node["template"]) { std::cout << "Error: Expecting \"template\" node"; }
         else { object.template_content = node["template"].as<std::string>(); }

         if (!node["variables"] || !node["variables"].IsSequence()) { std::cout << "Error: Expecting \"variables\" sequence"; }
         else
         {
            YAML::Node variables = node["variables"];
            for (std::size_t i=0; i<variables.size(); i++)
            {
               if (!variables[i].IsScalar()) { std::cout << "Error: Expecting \"variables\" element to be scalar"; }
               else { object.variables.push_back(variables[i].as<std::string>()); }
            }
         }

         return true;
      }
   };
}



#include <fstream>
class CodeTemplateRepository
{
private:
   std::string file_get_contents(std::string filename)
   {
      std::ifstream file(filename.c_str());
      std::string input = "";
      if (!file) return "";
      char ch;
      while (file.get(ch)) input.append(1, ch);
      if (!file.eof()) return ""; // strange error
      file.close();
      return input;
   }

   std::map<std::string, CodeTemplate> code_templates;


public:
   int num_templates()
   {
      return code_templates.size();
   }

   std::vector<std::string> names()
   {
      std::vector<std::string> result;
      for (std::map<std::string, CodeTemplate>::iterator it = code_templates.begin(); it != code_templates.end(); ++it)
      {
        result.push_back(it->first);
      }
      return result;
   }

   bool exists(std::string name)
   {
      std::map<std::string, CodeTemplate>::iterator it = code_templates.find(name);
      if (it != code_templates.end()) return true;
      return false;
   }

   CodeTemplate find_by_name(std::string name)
   {
      if (!exists(name)) throw std::runtime_error("find_by_name error: key \"(unset)\" does not exist");
      return code_templates[name];
   }

   void load_from_yaml_file(std::string filename)
   {
      std::string yaml_file_content = file_get_contents(filename);
      YAML::Node templates = YAML::Load(yaml_file_content);

      for (std::size_t i=0; i<templates.size(); i++)
      {
         CodeTemplate tmpl = templates[i].as<CodeTemplate>();
         code_templates[tmpl.name] = tmpl;
         //code_templates.push_back(tmpl);
      }
   }
};





std::string guard_throw_with_error_message_fun(std::string condition, std::string class_name, std::string function_name, std::string message)
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

   std::string filename = "/Users/markoates/Repos/hexagon/bin/programs/data/files/templates.yml";
   CodeTemplateRepository repository;
   repository.load_from_yaml_file(filename);

   std::cout << "num templates: " << repository.num_templates() << std::endl;
   for (auto &str : repository.names())
   {
      std::cout << "   - " << str << std::endl;
   }

   std::cout << "looking for key \"range_loop\": " << (repository.exists("range_loop") ? "exists!" : "does not exist!") << std::endl;
   std::cout << "looking for key \"key_that_does_not_exist\": " << (repository.exists("key_that_does_not_exist") ? "exists!" : "does not exist!") << std::endl;

   CodeTemplate guard_throw_with_error_message_template = repository.find_by_name("guard_throw_with_error_message");
   std::string filled = guard_throw_with_error_message_template.fill({
      { "{{CONDITION}}", "!argument" },
      { "{{CLASS_NAME}}", "Foobar::ClassName" },
      { "{{FUNCTION_NAME}}", "doing_the_thing" },
      { "{{MESSAGE}}", "argument cannot be a nullptr" },
   });

   std::cout << divider() << std::endl;
   std::cout << filled;
   std::cout << divider() << std::endl;

   return 0;
}
