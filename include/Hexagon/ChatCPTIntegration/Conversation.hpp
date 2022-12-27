#pragma once


#include <Hexagon/ChatCPTIntegration/Messages/Base.hpp>
#include <Hexagon/ChatGPTIntegration/Author.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>


namespace Hexagon
{
   namespace ChatCPTIntegration
   {
      class Conversation
      {
      private:
         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> messages;
         std::map<std::string, Hexagon::ChatGPTIntegration::Author> authors;

      protected:


      public:
         Conversation();
         ~Conversation();

         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> get_messages() const;
         std::map<std::string, Hexagon::ChatGPTIntegration::Author> get_authors() const;
         void append_text_message(std::string body="[unset-append_text_message]");
         void clear();
         std::vector<Hexagon::ChatCPTIntegration::Messages::Base*> get_last_n_messages(uint32_t count=3);
         void build_known_authors();
         Hexagon::ChatGPTIntegration::Author* find_author_by_identifier(std::string author_identifier="[unset-author_identifier]");
         bool author_exists(std::string author_identifier="[unset-author_identifier]");
         void load_from_log_text_file(std::string log_text_filename="[unset-log_text_filename]");
      };
   }
}



