

#include <Hexagon/BuildSystem/BuildStages/BuildQuintessence.hpp>



namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStages
{


BuildQuintessence::BuildQuintessence(std::string property)
   : Hexagon::BuildSystem::BuildStages::Base("BuildQuintessence")
   , property(property)
{
}


BuildQuintessence::~BuildQuintessence()
{
}


std::string BuildQuintessence::get_property() const
{
   return property;
}


bool BuildQuintessence::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}
} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


