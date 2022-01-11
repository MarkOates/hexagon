

#include <Hexagon/Daemus/Stage.hpp>



namespace Hexagon
{
namespace Daemus
{


Stage::Stage()
   : daemus()
{
}


Stage::~Stage()
{
}


void Stage::render()
{
   render_builds_list();
   return;
}

void Stage::render_builds_list()
{
   std::vector<Hexagon::Daemus::Builds::Base*> &builds = daemus.get_builds_ref();
   return;
}
} // namespace Daemus
} // namespace Hexagon


