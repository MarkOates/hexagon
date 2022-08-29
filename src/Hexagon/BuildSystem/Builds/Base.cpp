

#include <Hexagon/BuildSystem/Builds/Base.hpp>



namespace Hexagon
{
namespace BuildSystem
{
namespace Builds
{


Base::Base(std::string type)
   : type(type)
   , started_at(0)
   , ended_at(0)
   , status("[unset-status]")
   , stages({})
{
}


Base::~Base()
{
}


void Base::set_started_at(float started_at)
{
   this->started_at = started_at;
}


void Base::set_ended_at(float ended_at)
{
   this->ended_at = ended_at;
}


void Base::set_status(std::string status)
{
   this->status = status;
}


void Base::set_stages(std::vector<Hexagon::BuildSystem::BuildStages::Base*> stages)
{
   this->stages = stages;
}


std::string Base::get_type() const
{
   return type;
}


float Base::get_started_at() const
{
   return started_at;
}


float Base::get_ended_at() const
{
   return ended_at;
}


std::string Base::get_status() const
{
   return status;
}


std::vector<Hexagon::BuildSystem::BuildStages::Base*> Base::get_stages() const
{
   return stages;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}
} // namespace Builds
} // namespace BuildSystem
} // namespace Hexagon


