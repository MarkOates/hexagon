

#include <Hexagon/Rails/ComponentLister.hpp>
#include <sstream>


namespace Hexagon
{
namespace Rails
{


ComponentLister::ComponentLister()
{
}


ComponentLister::~ComponentLister()
{
}


std::vector<std::string> ComponentLister::model_filenames()
{
std::string project_root_directory = "/Users/markoates/Repos/disclife";
std::string fragment_folder_name = "app/models";
std::string fragment_extension = ".rb";

std::stringstream find_command;
find_command << "cd "
             << project_root_directory
             << " && find "
             << fragment_folder_name
             << " -type f -name \"*"
             << fragment_extension
             << "\""
             << " -o"
             << " -type l -name \"*"
             << fragment_extension
             << "\"";
 return {};

}
} // namespace Rails
} // namespace Hexagon


