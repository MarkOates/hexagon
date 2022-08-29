

#include <Hexagon/BuildSystem/BuildStages/Basic.hpp>



namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStages
{


Basic::Basic(std::string property)
   : Hexagon::BuildSystem::BuildStages::Base("Basic")
   , property(property)
{
}


Basic::~Basic()
{
}


std::string Basic::get_property() const
{
   return property;
}


bool Basic::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}
} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


