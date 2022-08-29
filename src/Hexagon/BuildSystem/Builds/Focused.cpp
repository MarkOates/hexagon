

#include <Hexagon/BuildSystem/Builds/Focused.hpp>



namespace Hexagon
{
namespace BuildSystem
{
namespace Builds
{


Focused::Focused(std::string property)
   : Hexagon::BuildSystem::Builds::Base("Focused")
   , property(property)
{
}


Focused::~Focused()
{
}


std::string Focused::get_property() const
{
   return property;
}


bool Focused::property_is(std::string possible_type)
{
   return (possible_type == get_property());
}
} // namespace Builds
} // namespace BuildSystem
} // namespace Hexagon


