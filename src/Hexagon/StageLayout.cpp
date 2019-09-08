

#include <Hexagon/StageLayout.hpp>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{


StageLayout::StageLayout(std::map<std::string, placement3d> placements)
   : placements(placements)
{
}


StageLayout::~StageLayout()
{
}


void StageLayout::set_placements(std::map<std::string, placement3d> placements)
{
   this->placements = placements;
}


std::map<std::string, placement3d> StageLayout::get_placements()
{
   return placements;
}


std::map<std::string, placement3d> &StageLayout::get_placements_ref()
{
   return placements;
}


placement3d StageLayout::placement_for(std::string label)
{
std::map<std::string, placement3d>::iterator it;
it = placements.find(label);
if (it == placements.end())
{
   std::stringstream error_message;
   error_message << "Could not find placement named \"" << label << "\"." << std::endl;
   throw std::runtime_error(error_message.str());
}
placement3d result = it->second;
return result;

}
} // namespace Hexagon


