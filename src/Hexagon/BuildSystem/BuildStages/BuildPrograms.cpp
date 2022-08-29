

#include <Hexagon/BuildSystem/BuildStages/BuildPrograms.hpp>



namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStages
{


BuildPrograms::BuildPrograms(std::string property)
   : Hexagon::BuildSystem::BuildStages::Base("BuildPrograms")
   , property(property)
{
}


BuildPrograms::~BuildPrograms()
{
}


std::string BuildPrograms::get_property() const
{
   return property;
}


bool BuildPrograms::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}
} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


