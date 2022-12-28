#pragma once


#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>
#include <Hexagon/ChatGPTIntegration/Author.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <utility>
#include <vector>


namespace Hexagon
{
   namespace ChatCPTIntegration
   {
      class Conversation
      {
      private:
         std::string conversation_id;
         std::string last_parent_id;
         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> messages;
         std::map<std::string, Hexagon::ChatGPTIntegration::Author> authors;

      protected:


      public:
         Conversation(std::string conversation_id="", std::string last_parent_id="");
         ~Conversation();

         void set_conversation_id(std::string conversation_id);
         void set_last_parent_id(std::string last_parent_id);
         std::string get_conversation_id() const;
         std::string get_last_parent_id() const;
         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> get_messages() const;
         std::map<std::string, Hexagon::ChatGPTIntegration::Author> get_authors() const;
         void append_text_message(uint32_t author_id=0, std::string body="[unset-append_text_message]");
         void clear();
         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> get_last_n_messages(uint32_t count=3);
         void build_known_authors();
         Hexagon::ChatGPTIntegration::Author* find_author_by_identifier(std::string author_identifier="[unset-author_identifier]");
         Hexagon::ChatGPTIntegration::Author* find_author_by_id(uint32_t author_id=0);
         bool author_exists(std::string author_identifier="[unset-author_identifier]");
         bool author_exists_by_id(uint32_t author_id=0);
         void load_from_log_text_file(std::string log_text_filename="[unset-log_text_filename]");
         Hexagon::ChatCPTIntegration::Messages::Base* get_most_recent_message();
         bool conversation_id_and_parent_id_data_are_empty(std::pair<std::string, std::string> conversation_id_and_parent_id={});
         std::pair<std::string, std::string> parse_conversation_id_and_parent_id_from_json_str(std::string json_str="[unset-json_str]");
      };
   }
}



