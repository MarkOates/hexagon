

#include <Hexagon/Daemus/Builds/Base.hpp>



namespace Hexagon
{
namespace Daemus
{
namespace Builds
{


Base::Base(std::string type)
   : type(type)
   , status("uninitialized")
{
}


Base::~Base()
{
}


std::string Base::get_type()
{
   return type;
}


std::string Base::get_status()
{
   return status;
}


void Base::initiate()
{
   return;
}
} // namespace Builds
} // namespace Daemus
} // namespace Hexagon


