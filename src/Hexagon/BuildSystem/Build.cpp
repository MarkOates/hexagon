

#include <Hexagon/BuildSystem/Build.hpp>



namespace Hexagon
{
namespace BuildSystem
{


std::string Build::STATUS_UNDEFINED = "undefined";


Build::Build()
   : status(STATUS_UNDEFINED)
{
}


Build::~Build()
{
}


std::string Build::get_status()
{
   return status;
}


std::string Build::start()
{
   return "Hello World!";
}
} // namespace BuildSystem
} // namespace Hexagon


