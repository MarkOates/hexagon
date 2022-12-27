

#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>




namespace Hexagon
{
namespace ChatCPTIntegration
{
namespace Messages
{


Base::Base(std::string type, int author_id)
   : type(type)
   , author_id(author_id)
{
}


Base::~Base()
{
}


void Base::set_author_id(int author_id)
{
   this->author_id = author_id;
}


std::string Base::get_type() const
{
   return type;
}


int Base::get_author_id() const
{
   return author_id;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Messages
} // namespace ChatCPTIntegration
} // namespace Hexagon


