

#include <Hexagon/ChatGPTIntegration/Message.hpp>




namespace Hexagon
{
namespace ChatGPTIntegration
{


Message::Message(std::string text, uint32_t author_id)
   : text(text)
   , author_id(author_id)
{
}


Message::~Message()
{
}


void Message::set_text(std::string text)
{
   this->text = text;
}


void Message::set_author_id(uint32_t author_id)
{
   this->author_id = author_id;
}


std::string Message::get_text() const
{
   return text;
}


uint32_t Message::get_author_id() const
{
   return author_id;
}




} // namespace ChatGPTIntegration
} // namespace Hexagon


