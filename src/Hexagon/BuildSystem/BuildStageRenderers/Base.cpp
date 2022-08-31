

#include <Hexagon/BuildSystem/BuildStageRenderers/Base.hpp>




namespace Hexagon
{
namespace BuildSystem
{
namespace BuildStageRenderers
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

std::string Base::render_text()
{
   return "";
}


} // namespace BuildStageRenderers
} // namespace BuildSystem
} // namespace Hexagon


