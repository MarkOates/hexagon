

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
   , mutex_for_started_at()
   , ended_at()
   , mutex_for_ended_at()
   , status("[unset-status]")
   , mutex_for_status()
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


std::string Base::get_status()
{
   std::string result;
   mutex_for_status.lock();
   result = status;
   mutex_for_status.unlock();
   return result;
}

void Base::set_status(std::string status)
{
   mutex_for_status.lock();
   this->status = status;
   mutex_for_status.unlock();
   return;
}

std::chrono::system_clock::time_point Base::get_started_at()
{
   std::chrono::system_clock::time_point result;
   mutex_for_started_at.lock();
   result = started_at;
   mutex_for_started_at.unlock();
   return result;
}

void Base::set_started_at(std::chrono::system_clock::time_point started_at)
{
   mutex_for_started_at.lock();
   this->started_at = started_at;
   mutex_for_started_at.unlock();
}

std::chrono::system_clock::time_point Base::get_ended_at()
{
   std::chrono::system_clock::time_point result;
   mutex_for_ended_at.lock();
   result = ended_at;
   mutex_for_ended_at.unlock();
   return result;
}

void Base::set_ended_at(std::chrono::system_clock::time_point ended_at)
{
   mutex_for_ended_at.lock();
   this->ended_at = ended_at;
   mutex_for_ended_at.unlock();
}

bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}

bool Base::execute()
{
   return true;
}

double Base::calc_duration_seconds()
{
   std::chrono::duration<double> elapsed_seconds = get_ended_at() - get_started_at();
   return elapsed_seconds.count();
}


} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


