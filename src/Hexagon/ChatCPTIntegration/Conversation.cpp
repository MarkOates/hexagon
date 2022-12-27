

#include <Hexagon/ChatCPTIntegration/Conversation.hpp>

#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>


namespace Hexagon
{
namespace ChatCPTIntegration
{


Conversation::Conversation()
   : messages()
{
}


Conversation::~Conversation()
{
}


void Conversation::append_text_message(std::string body)
{
   Hexagon::ChatCPTIntegration::Messages::Text *result = new Hexagon::ChatCPTIntegration::Messages::Text(body);
   messages.push_back(result);
   return;
}

std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> Conversation::get_last_n_messages(uint32_t count)
{
   std::vector<Messages::Base*> lastNMessages;

   // Make sure n is not greater than the number of messages in the vector
   if (count > messages.size()) {
       count = messages.size();
   }

   // Start from the end of the vector and work backwards, adding the
   // last n messages to the lastNMessages vector
   for (int i = messages.size() - 1; i >= messages.size() - count; i--) {
       lastNMessages.push_back(messages[i]);
   }

   return lastNMessages;
}


} // namespace ChatCPTIntegration
} // namespace Hexagon


