

#include <Hexagon/ChatCPTIntegration/Conversation.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <Blast/String/Trimmer.hpp>
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
   , authors()
{
}


Conversation::~Conversation()
{
}


std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> Conversation::get_messages() const
{
   return messages;
}


std::map<std::string, Hexagon::ChatGPTIntegration::Author> Conversation::get_authors() const
{
   return authors;
}


void Conversation::append_text_message(uint32_t author_id, std::string body)
{
   Hexagon::ChatCPTIntegration::Messages::Text *result = new Hexagon::ChatCPTIntegration::Messages::Text(body);
   result->set_author_id(author_id);
   messages.push_back(result);
   return;
}

void Conversation::clear()
{
   for (auto &message : messages) { delete message; }
   messages.clear();
   authors.clear();
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

void Conversation::build_known_authors()
{
   using Hexagon::ChatGPTIntegration::Author;
   authors["unknown"] = Author(0, "unknown", "Unknown", "");
   authors["mark_oates"] = Author(1, "mark_oates", "MarkOates", "mark-oates-avatar-01.png", al_color_html("2b313b"));
   authors["chat_gpt"] = Author(2, "chat_gpt", "ChatGPT", "rubber-duck-avatar-01.png", al_color_html("2b1c2b"));
   authors["rev_chat_gpt"] = Author(3, "rev_chat_gpt", "[System]", "", al_color_html("77162a"));
   return;
}

Hexagon::ChatGPTIntegration::Author* Conversation::find_author_by_identifier(std::string author_identifier)
{
   if (!author_exists(author_identifier)) return nullptr;
   Hexagon::ChatGPTIntegration::Author* found_author = &authors[author_identifier];
   return found_author;
}

Hexagon::ChatGPTIntegration::Author* Conversation::find_author_by_id(uint32_t author_id)
{
   for (auto &author : authors) if (author.second.get_id() == author_id) return &author.second;
   return nullptr;
}

bool Conversation::author_exists(std::string author_identifier)
{
   return (authors.count(author_identifier) == 1);
}

bool Conversation::author_exists_by_id(uint32_t author_id)
{
   for (auto &author : authors) if (author.second.get_id() == author_id) return true;
   return false;
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

   build_known_authors();


   std::vector<std::string> lines = Blast::StringSplitter(log_text, '\n').split();
   int32_t state = 0; // 0 nothing, 1 parsing prompt, 2 parsing response, 3 response info, 4 parsing error
   std::vector<std::string> accumulated_lines;
   for (auto &line : lines)
   {
      if (line == "========== PROMPT BEGIN ==========") { accumulated_lines.clear(); state = 1; continue; }
      if (line == "========== RESPONSE BEGIN ==========") { accumulated_lines.clear(); state = 2; continue; }
      if (line == "========== RESPONSE INFO BEGIN ==========") { accumulated_lines.clear(); state = 3; continue; }
      if (line == "========== ERROR BEGIN ==========") { accumulated_lines.clear(); state = 4; continue; }

      if (line == "========== PROMPT END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         append_text_message(1, Blast::String::Trimmer(joined_accumulated_lines).trim());
         accumulated_lines.clear();
         state = 0;
         continue;
      }
      if (line == "========== RESPONSE END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         append_text_message(2, Blast::String::Trimmer(joined_accumulated_lines).trim());
         accumulated_lines.clear();
         state = 0;
         continue;
      }
      if (line == "========== RESPONSE INFO END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         append_text_message(3, Blast::String::Trimmer(joined_accumulated_lines).trim());
         accumulated_lines.clear();
         state = 0;
         continue;
      }
      if (line == "========== ERROR END ==========")
      {
         std::string joined_accumulated_lines = Blast::StringJoiner(accumulated_lines, "\n").join();
         append_text_message(3, Blast::String::Trimmer(joined_accumulated_lines).trim());
         accumulated_lines.clear();
         state = 0;
         continue;
      }

      accumulated_lines.push_back(line);
   }
}


} // namespace ChatCPTIntegration
} // namespace Hexagon


