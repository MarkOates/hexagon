

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


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}
} // namespace Builds
} // namespace BuildSystem
} // namespace Hexagon


