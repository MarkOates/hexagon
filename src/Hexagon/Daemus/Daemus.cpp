

#include <Hexagon/Daemus/Daemus.hpp>



namespace Hexagon
{
namespace Daemus
{


Daemus::Daemus()
   : current_build(nullptr)
   , builds({})
{
}


Daemus::~Daemus()
{
}


Hexagon::Daemus::Builds::Base* Daemus::get_current_build()
{
   return current_build;
}


std::vector<Hexagon::Daemus::Builds::Base*> &Daemus::get_builds_ref()
{
   return builds;
}


Hexagon::Daemus::Builds::ExtrapolateQuintessence* Daemus::create_extrapolate_quintessence_build()
{
   Hexagon::Daemus::Builds::ExtrapolateQuintessence* result = new Hexagon::Daemus::Builds::ExtrapolateQuintessence();
   return result;
}
} // namespace Daemus
} // namespace Hexagon


