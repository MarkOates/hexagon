

#include <Hexagon/ChatGPTIntegration/Author.hpp>




namespace Hexagon
{
namespace ChatGPTIntegration
{


Author::Author(uint32_t id, std::string identifier, std::string name, std::string avatar_bitmap_identifier)
   : id(id)
   , identifier(identifier)
   , name(name)
   , avatar_bitmap_identifier(avatar_bitmap_identifier)
{
}


Author::~Author()
{
}


void Author::set_id(uint32_t id)
{
   this->id = id;
}


void Author::set_identifier(std::string identifier)
{
   this->identifier = identifier;
}


void Author::set_name(std::string name)
{
   this->name = name;
}


void Author::set_avatar_bitmap_identifier(std::string avatar_bitmap_identifier)
{
   this->avatar_bitmap_identifier = avatar_bitmap_identifier;
}


uint32_t Author::get_id() const
{
   return id;
}


std::string Author::get_identifier() const
{
   return identifier;
}


std::string Author::get_name() const
{
   return name;
}


std::string Author::get_avatar_bitmap_identifier() const
{
   return avatar_bitmap_identifier;
}




} // namespace ChatGPTIntegration
} // namespace Hexagon


