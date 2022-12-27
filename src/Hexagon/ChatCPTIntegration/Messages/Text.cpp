

#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>




namespace Hexagon
{
namespace ChatCPTIntegration
{
namespace Messages
{


Text::Text(std::string body)
   : Hexagon::ChatCPTIntegration::Messages::Base(Hexagon::ChatCPTIntegration::Messages::Text::TYPE)
   , body(body)
{
}


Text::~Text()
{
}


void Text::set_body(std::string body)
{
   this->body = body;
}


std::string Text::get_body() const
{
   return body;
}




} // namespace Messages
} // namespace ChatCPTIntegration
} // namespace Hexagon


