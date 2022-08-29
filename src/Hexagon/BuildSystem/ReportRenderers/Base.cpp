

#include <Hexagon/BuildSystem/ReportRenderers/Base.hpp>



namespace Hexagon
{
namespace BuildSystem
{
namespace ReportRenderers
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

std::string Base::render()
{
   return;
}
} // namespace ReportRenderers
} // namespace BuildSystem
} // namespace Hexagon


