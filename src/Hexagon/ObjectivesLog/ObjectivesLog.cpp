

#include <Hexagon/ObjectivesLog/ObjectivesLog.hpp>



namespace Hexagon
{
namespace ObjectivesLog
{


ObjectivesLog::ObjectivesLog()
   : objectives({})
{
}


ObjectivesLog::~ObjectivesLog()
{
}


std::vector<Hexagon::ObjectivesLog::Objective> &ObjectivesLog::get_objectives_ref()
{
   return objectives;
}


void ObjectivesLog::add_objective(Hexagon::ObjectivesLog::Objective objective)
{
   objectives.push_back(objective);
   return;
}
} // namespace ObjectivesLog
} // namespace Hexagon


