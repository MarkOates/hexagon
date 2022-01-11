

#include <Hexagon/Daemus/Builds/Base.hpp>



namespace Hexagon
{
namespace Daemus
{
namespace Builds
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type()
{
   return type;
}


std::string Base::run()
{
   return "Hello World!";
}
} // namespace Builds
} // namespace Daemus
} // namespace Hexagon


