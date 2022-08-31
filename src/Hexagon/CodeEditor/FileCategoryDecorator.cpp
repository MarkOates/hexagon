

#include <Hexagon/CodeEditor/FileCategoryDecorator.hpp>

#include <map>
#include <string>


namespace Hexagon
{
namespace CodeEditor
{


FileCategoryDecorator::FileCategoryDecorator(std::string file_category)
   : file_category(file_category)
{
}


FileCategoryDecorator::~FileCategoryDecorator()
{
}


std::string FileCategoryDecorator::label()
{
   std::string result = "";
   std::map<std::string, std::string> file_category_labels = {
     { "undefined", "Undefined" },
     { "blast_quintessence", "Quintessence" },
     { "blast_test", "Test" },
     { "cpp_header", "Header" },
     { "cpp_source", "Source" },
     { "rails_model", "Model" },
     { "rails_model_test", "Model Test" },
     { "rails_controller", "Controller" },
     { "rails_controller_test", "Controller Test" },
     { "rails_routes", "Routes" },
   };

   std::map<std::string, std::string>::iterator it = file_category_labels.find(file_category);
   bool category_label_exists = (it != file_category_labels.end());
   if (!category_label_exists)
   {
      result = "Unknown";
   }
   else
   {
      result = it->second;
   }

   return result;
}


} // namespace CodeEditor
} // namespace Hexagon


