

#include <Hexagon/ChatCPTIntegration/Conversation.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>
#include <allegro_flare/useful_php.h>


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


std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> Conversation::get_messages() const
{
   return messages;
}


void Conversation::append_text_message(std::string body)
{
   Hexagon::ChatCPTIntegration::Messages::Text *result = new Hexagon::ChatCPTIntegration::Messages::Text(body);
   messages.push_back(result);
   return;
}

void Conversation::clear()
{
   for (auto &message : messages) { delete message; }
   messages.clear();
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

void Conversation::load_from_log_text_file(std::string log_text_filename)
{
   Blast::FileExistenceChecker existence_checker(log_text_filename);
   if (!existence_checker.exists())
   {
      // TODO: output this message in the chat window
      std::cout << "[ file not found at expected location ]\n[ looking in " + log_text_filename + " ]" << std::endl;
   }
   std::string log_text = php::file_get_contents(log_text_filename);

   clear();
   std::vector<std::string> lines = Blast::StringSplitter(log_text, '\n').split();
   int32_t state = 0; // 0 nothing, 1 parsing prompt, 2 parsing response, 3 response info, 4 parsing error
   std::vector<std::string> accumulated_lines;
   for (auto &line : lines)
   {
      if (line == "========== PROMPT BEGIN ==========") { state = 1; continue; }
      if (line == "========== RESPONSE BEGIN ==========") { state = 2; continue; }
      if (line == "========== RESPONSE INFO BEGIN ==========") { state = 3; continue; }
      if (line == "========== ERROR BEGIN ==========") { state = 4; continue; }

      if (line == "========== PROMPT END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         //Hexagon::ChatCPTIntegration::Messages::Text* result =
            //new Hexagon::ChatCPTIntegration::Messages::Text(joined_accumulated_lines);
         append_text_message(joined_accumulated_lines);
         
         accumulated_lines.clear();
         state = 0;
         continue;
      }
      if (line == "========== RESPONSE END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         append_text_message(joined_accumulated_lines);
         accumulated_lines.clear();
         state = 0;
         continue;
      }
      if (line == "========== RESPONSE INFO END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         append_text_message(joined_accumulated_lines);
         accumulated_lines.clear();
         state = 0;
         continue;
      }
      if (line == "========== ERROR END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         append_text_message(joined_accumulated_lines);
         accumulated_lines.clear();
         state = 0;
         continue;
      }
   }
}


} // namespace ChatCPTIntegration
} // namespace Hexagon


