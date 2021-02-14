

#include <Hexagon/FilesOpenedHistory.hpp>



namespace Hexagon
{


FilesOpenedHistory::FilesOpenedHistory(std::vector<std::string> files)
   : files(files)
{
}


FilesOpenedHistory::~FilesOpenedHistory()
{
}


std::vector<std::string> FilesOpenedHistory::get_files()
{
   return files;
}


std::string FilesOpenedHistory::run()
{
   return "Hello World!";
}
} // namespace Hexagon


