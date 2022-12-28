

#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>




namespace Hexagon
{
namespace ChatCPTIntegration
{
namespace Messages
{


Base::Base(std::string type, int author_id, std::string conversation_id, std::string parent_id)
   : type(type)
   , author_id(author_id)
   , conversation_id(conversation_id)
   , parent_id(parent_id)
{
}


Base::~Base()
{
}


void Base::set_author_id(int author_id)
{
   this->author_id = author_id;
}


void Base::set_conversation_id(std::string conversation_id)
{
   this->conversation_id = conversation_id;
}


void Base::set_parent_id(std::string parent_id)
{
   this->parent_id = parent_id;
}


std::string Base::get_type() const
{
   return type;
}


int Base::get_author_id() const
{
   return author_id;
}


std::string Base::get_conversation_id() const
{
   return conversation_id;
}


std::string Base::get_parent_id() const
{
   return parent_id;
}


bool Base::is_type(std::string possible_type)
{
   return (possible_type == get_type());
}


} // namespace Messages
} // namespace ChatCPTIntegration
} // namespace Hexagon


