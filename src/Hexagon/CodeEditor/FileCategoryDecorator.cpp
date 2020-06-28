

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
std::map<std::string, std::string> file_category_labels = {
  { "undefined", "Undefined" },
};

return "Undefined";

}
} // namespace CodeEditor
} // namespace Hexagon


