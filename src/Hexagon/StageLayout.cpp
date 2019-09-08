

#include <Hexagon/StageLayout.hpp>



namespace Hexagon
{


StageLayout::StageLayout(std::map<std::string, placement3d> placements)
   : placements(placements)
{
}


StageLayout::~StageLayout()
{
}


std::map<std::string, placement3d> StageLayout::get_placements()
{
   return placements;
}


std::string StageLayout::run()
{
return "Hello Buddy!";
}

placement3d StageLayout::placement_for(std::string label)
{
placement3d result;
return result;

}
} // namespace Hexagon


