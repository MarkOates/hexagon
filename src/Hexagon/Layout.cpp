

#include <Hexagon/Layout.hpp>



namespace Hexagon
{


Layout::Layout(std::string concept_name, std::vector<std::tuple<std::string, std::string, placement3d>> files, std::string daemus_command)
   : concept_name(concept_name)
   , files(files)
   , daemus_command(daemus_command)
{
}


Layout::~Layout()
{
}


void Layout::set_concept_name(std::string concept_name)
{
   this->concept_name = concept_name;
}


void Layout::set_files(std::vector<std::tuple<std::string, std::string, placement3d>> files)
{
   this->files = files;
}


std::string Layout::get_concept_name()
{
   return concept_name;
}


std::vector<std::tuple<std::string, std::string, placement3d>> Layout::get_files()
{
   return files;
}


std::string Layout::get_daemus_command()
{
   return daemus_command;
}


std::vector<std::tuple<std::string, std::string, placement3d>> &Layout::get_files_ref()
{
   return files;
}


} // namespace Hexagon


