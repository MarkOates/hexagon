

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


} // namespace ObjectivesLog
} // namespace Hexagon


