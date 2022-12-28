

#include <Hexagon/ChatCPTIntegration/Conversation.hpp>

#include <Blast/FileExistenceChecker.hpp>
#include <Blast/String/Trimmer.hpp>
#include <Blast/StringJoiner.hpp>
#include <Blast/StringSplitter.hpp>
#include <Hexagon/ChatCPTIntegration/Messages/Text.hpp>
#include <allegro_flare/useful_php.h>
#include <lib/nlohmann/json.hpp>


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
   // Make sure n is not greater than the number of messages in the vector
   if (count > messages.size()) {
       count = messages.size();
   }

   std::vector<Messages::Base*> result(messages.end() - count, messages.end());

   return result;
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
         std::string trimmed_lines = Blast::String::Trimmer(joined_accumulated_lines).trim();
         std::pair<std::string, std::string> conversation_id_and_parent_id =
            parse_conversation_id_and_parent_id_from_json_str(trimmed_lines);

         if (conversation_id_and_parent_id_data_are_empty(conversation_id_and_parent_id))
         {
            // Note: conversation_id and parent_id could not be parsed from this RESPONSE INFO section
            // Include a warning message with the text body
            trimmed_lines = "[Hexagon::ChatCPTIntegration::Conversation]: warning: A parse error occurred and it "
                            "was not possible to obtain the conversation_id and parent_id from the RESPONSE INFO. "
                            "The response contained the following content (which could be empty): " + trimmed_lines;
         }
         else
         {
            // Append conversation_id and parent_id to the most recent message

            Hexagon::ChatCPTIntegration::Messages::Base* most_recent_message = get_most_recent_message();
            if (!most_recent_message)
            {
               // A weird error occurred
               // TODO: consider what the proper error response should be in this condition. For now, doing cout:
               std::cout << "An error occurred when trying to get_most_recent_message() in order to append "
                         << "the conversation_id and parent_id to the most recent message, which came back as "
                         << "a nullptr.";
            }
            else
            {
               // TODO: Consider if it's necessary to validate the type of the previous message, e.g., make sure it's
               // from author_id 2.
               most_recent_message->set_conversation_id(conversation_id_and_parent_id.first);
               most_recent_message->set_parent_id(conversation_id_and_parent_id.second);
            }
         }

         append_text_message(3, trimmed_lines);
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

Hexagon::ChatCPTIntegration::Messages::Base* Conversation::get_most_recent_message()
{
   if (messages.empty()) return nullptr;
   return messages.back();
}

bool Conversation::conversation_id_and_parent_id_data_are_empty(std::pair<std::string, std::string> conversation_id_and_parent_id)
{
   return conversation_id_and_parent_id.first.empty() && conversation_id_and_parent_id.second.empty();
}

std::pair<std::string, std::string> Conversation::parse_conversation_id_and_parent_id_from_json_str(std::string json_str)
{
   try
   {
      nlohmann::json json = nlohmann::json::parse(json_str);
      bool contains_conversation_id = json.contains("conversation_id");
      bool contains_parent_id = json.contains("parent_id");

      if (!contains_conversation_id || !contains_parent_id)
      {
         std::cout << "An error occurred when trying to parse the json output in RESPONSE INFO. "
                   << "Expecting the json to contain \"conversation_id\" and \"parent_id\" keys, but it does not."
                   << std::endl;
      }
      else
      {
         return std::pair<std::string, std::string>(
            json["conversation_id"].get<std::string>(),
            json["parent_id"].get<std::string>()
         );
      }
   }
   catch (const std::exception& e)
   {
      std::cout << "An error occurred when trying to parse the json output in RESPONSE INFO. "
                << "The following exception was thrown: " << e.what() << " on the following json input string: "
                << json_str << std::endl;
   }
   return std::pair<std::string, std::string>("", "");
}


} // namespace ChatCPTIntegration
} // namespace Hexagon


