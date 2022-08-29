

#include <Hexagon/BuildSystem/BuildStages/Base.hpp>



namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStages
{


Base::Base(std::string type)
   : type(type)
{
}


Base::~Base()
{
}


std::string Base::get_type() const
{
   return type;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}
} // namespace BuildStages
} // namespace BuildSystem
} // namespace Hexagon


