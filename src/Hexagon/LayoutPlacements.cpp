

#include <Hexagon/LayoutPlacements.hpp>
#include <sstream>
#include <stdexcept>


namespace Hexagon
{


LayoutPlacements::LayoutPlacements(std::map<std::string, placement3d> placements)
   : placements(placements)
{
}


LayoutPlacements::~LayoutPlacements()
{
}


void LayoutPlacements::set_placements(std::map<std::string, placement3d> placements)
{
   this->placements = placements;
}


std::map<std::string, placement3d> LayoutPlacements::get_placements() const
{
   return placements;
}


std::map<std::string, placement3d> &LayoutPlacements::get_placements_ref()
{
   return placements;
}


placement3d LayoutPlacements::placement_for(std::string label)
{
   std::map<std::string, placement3d>::iterator it;
   it = placements.find(label);
   if (it == placements.end())
   {
      std::stringstream error_message;
      error_message << "Could not find a layout position labeled \"" << label << "\"." << std::endl;
      throw std::runtime_error(error_message.str());
   }
   placement3d result = it->second;
   return result;
}
} // namespace Hexagon


