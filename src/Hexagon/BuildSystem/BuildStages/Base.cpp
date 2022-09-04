

#include <Hexagon/BuildSystem/BuildStages/Base.hpp>




namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStages
{


Base::Base(std::string type)
   : type(type)
   , started_at()
   , ended_at()
   , status("[unset-status]")
   , mutex_for_status()
{
}


Base::~Base()
{
}


void Base::set_started_at(std::chrono::system_clock::time_point started_at)
{
   this->started_at = started_at;
}


void Base::set_ended_at(std::chrono::system_clock::time_point ended_at)
{
   this->ended_at = ended_at;
}


void Base::set_status(std::string status)
{
   this->status = status;
}


std::string Base::get_type() const
{
   return type;
}


std::chrono::system_clock::time_point Base::get_started_at() const
{
   return started_at;
}


std::chrono::system_clock::time_point Base::get_ended_at() const
{
   return ended_at;
}


std::string Base::get_status() const
{
   return status;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

void Base::execute()
{
   return;
}

double Base::calc_duration_seconds()
{
   std::chrono::duration<double> elapsed_seconds = ended_at - started_at;
   return elapsed_seconds.count();
}


} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


