

#include <Hexagon/Layout.hpp>



namespace Hexagon
{


Layout::Layout(std::string project_root, std::vector<std::tuple<std::string, float, float>> file, std::string daemus_command)
   : project_root(project_root)
   , file(file)
   , daemus_command(daemus_command)
{
}


Layout::~Layout()
{
}


void Layout::set_file(std::vector<std::tuple<std::string, float, float>> file)
{
   this->file = file;
}


std::string Layout::get_project_root()
{
   return project_root;
}


std::vector<std::tuple<std::string, float, float>> Layout::get_file()
{
   return file;
}


std::string Layout::get_daemus_command()
{
   return daemus_command;
}


} // namespace Hexagon


